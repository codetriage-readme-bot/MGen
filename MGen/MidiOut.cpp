#include "stdafx.h"
#include "MidiOut.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CMidiOut::CMidiOut()
{
	rmo = 0;
}

CMidiOut::~CMidiOut()
{
	StopMidi();
}

int CMidiOut::StartMidi(int port)
{
	try {
		// Open RtMidi
		rmo = new RtMidiOut();
		rmo->openPort(port);
		// Begin MIDI playback thread
		m_MidiThread = AfxBeginThread(MidiThread, this, THREAD_PRIORITY_TIME_CRITICAL);
	}
	catch (RtMidiError &error) {
		m_error = error.getMessage().c_str();
		m_error_type = error.getType();
		return 1;
	}

	return 0;
}

int CMidiOut::StopMidi()
{
	// Send signal to thread
	need_exit = 1;
	// Wait for thread to exit
	WaitForSingleObject(m_MidiThread->m_hThread, 10000);
	// Clear if needed
	if (rmo) {
		delete rmo;
		rmo = 0;
	}
	return 0;
}

int CMidiOut::QueueEvent(PmEvent event)
{
	q.enqueue(event);
	return 0;
}

UINT CMidiOut::MidiThread(LPVOID pParam)
{
	// Need to get pointer to this object, because thread function is static
	CMidiOut* pMO = (CMidiOut*)pParam;
	// if Object is not valid  
	if (pMO == NULL) return 1;
	PmEvent event;
	mMessage message(3);
	PmTimestamp timestamp_current;
	int wait_time, wait_time_left;
	while (true) {
		// Check if we need to exit
		if (pMO->need_exit) break;
		// Wait for next event with timeout
		if (pMO->q.wait_dequeue_timed(event, milliseconds(WAIT_MS))) {
			// Check if we need to exit
			if (pMO->need_exit) break;
			// Get current timestamp
			timestamp_current = TIME_PROC(TIME_INFO);
			wait_time = event.timestamp - timestamp_current;
			// Wait for event timestamp
			wait_time_left = wait_time;
			if (wait_time > 0) {
				// Split long waiting into cycles to check for exit
				while (wait_time_left > WAIT_MS) {
					Sleep(WAIT_MS);
					wait_time_left -= WAIT_MS;
					// Check if we need to exit
					if (pMO->need_exit) break;
				}
				Sleep(wait_time_left);
			}
			// Convert to mMessage
			message[0] = Pm_MessageStatus(event.message);
			message[1] = Pm_MessageData1(event.message);
			message[2] = Pm_MessageData2(event.message);
			// Send event
			pMO->rmo->sendMessage(&message);
		}
	}
	return 0;
}
