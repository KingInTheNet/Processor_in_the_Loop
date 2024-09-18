/*createHandle.h
 * contains the function for opening a serial communication port
 * Properties are specified here. These properties will rarely need editing
 * The function returns the handle used for read/write commands
 * This file is also used for creating the send and receive MEX functions. Do not edit*/

#include <stdio.h>
#include <windows.h>

HANDLE createHandle(char commPortName[], int port_baud_rate, int port_stopbits){
    
    HANDLE hPort = CreateFile(commPortName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    
    if(hPort == INVALID_HANDLE_VALUE) {
        printf("hPort INVALID\n --> please close all other windows using the specified port\n");
    }
    else{
        DCB PortDCB;
        //COMMTIMEOUTS CommTimeouts;
        
        // Configure the port according to the specifications of the DCB structure.
        PortDCB.DCBlength = sizeof (DCB);     // Get the default port setting information.
        GetCommState (hPort, &PortDCB);       // Change the DCB structure settings.
        PortDCB.BaudRate = port_baud_rate;    // Current baud
        PortDCB.fBinary = TRUE;               // Binary mode; no EOF check
        PortDCB.fParity = TRUE;               // Enable parity checking
        PortDCB.fOutxCtsFlow = FALSE;         // No CTS output flow control
        PortDCB.fOutxDsrFlow = FALSE;         // No DSR output flow control
        PortDCB.fDtrControl = DTR_CONTROL_ENABLE;     // DTR flow control type
        PortDCB.fDsrSensitivity = FALSE;      // DSR sensitivity
        PortDCB.fTXContinueOnXoff = TRUE;     // XOFF continues Tx
        PortDCB.fOutX = FALSE;                // No XON/XOFF out flow control
        PortDCB.fInX = FALSE;                 // No XON/XOFF in flow control
        PortDCB.fErrorChar = FALSE;           // Disable error replacement
        PortDCB.fNull = FALSE;                // Disable null stripping
        PortDCB.fRtsControl = RTS_CONTROL_ENABLE;     // RTS flow control
        PortDCB.fAbortOnError = FALSE;        // Do not abort reads/writes on error
        PortDCB.ByteSize = 8;                 // Number of bits/byte, 4-8  (matlab only supports multiples of 8)
        PortDCB.Parity = NOPARITY;            // 0-4=no,odd,even,mark,space
        PortDCB.StopBits = port_stopbits;        // 0,1,2 = 1, 1.5, 2
        
        // Retrieve the timeout parameters for all read and write operations on the port.
        if(!SetCommState (hPort, &PortDCB)){
            printf("SetCommState failed\n");
            return FALSE;
        }
    }
    SetCommMask(hPort,EV_RXCHAR);
    
    return hPort;
}