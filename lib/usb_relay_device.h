#ifndef USB_RELAY_DEVICE_H__
#define USB_RELAY_DEVICE_H__

#ifdef WIN32
#ifndef USBRL_API
#  define USBRL_API __declspec(dllimport)
#endif
#ifndef CDECL
#  define CDECL _cdecl
#endif
#
#else /* !WIN32 */
#
#ifndef USBRL_API
#  define USBRL_API
#endif
#ifndef CDECL
#  define CDECL
#endif
#
#endif /* WIN32 */

#include <stddef.h>

enum usb_relay_device_type
{
    USB_RELAY_DEVICE_ONE_CHANNEL   = 1,
    USB_RELAY_DEVICE_TWO_CHANNEL   = 2,
    USB_RELAY_DEVICE_FOUR_CHANNEL  = 4,
    USB_RELAY_DEVICE_EIGHT_CHANNEL = 8	
};


/** USB relay board info structure*/
struct usb_relay_device_info
{
    unsigned char *serial_number;
    char *device_path;
    enum usb_relay_device_type type;
    struct usb_relay_device_info* next;
};

#ifdef __cplusplus
extern "C" {
#endif

/** Initialize the USB Relay Library
@returns: This function returns 0 on success and -1 on error.
*/
USBRL_API 
int CDECL usb_relay_init(void);

/** Finalize the USB Relay Library.
This function frees all of the static data associated with USB Relay Library. 
It should be called at the end of execution to avoid memory leaks.
@returns:This function returns 0 on success and -1 on error.
*/
USBRL_API 
int CDECL usb_relay_exit(void);


/** Enumerate the USB Relay Devices.*/
USBRL_API 
struct usb_relay_device_info * CDECL usb_relay_device_enumerate(void);


/** Free an enumeration Linked List*/
USBRL_API
void CDECL usb_relay_device_free_enumerate(struct usb_relay_device_info*);

/** Open device that serial number is serial_number
@return: This function returns a valid handle to the device on success or NULL on failure.
e.g: usb_relay_device_open_with_serial_number("abcde", 5") */
USBRL_API
intptr_t CDECL usb_relay_device_open_with_serial_number(const char *serial_number, unsigned len);

/* Open a USB relay device
@return: This function returns a valid handle to the device on success or NULL on failure.
*/
USBRL_API 
intptr_t CDECL usb_relay_device_open(struct usb_relay_device_info *device_info);

/* Close a USB relay device*/
USBRL_API 
void CDECL usb_relay_device_close(intptr_t hHandle);

/** Turn ON a relay channel on the USB-Relay-Device
@param hHandle -- which usb relay device your want to operate
@param index -- the channel number: 1...max
@returns: 0 -- success; 1 -- error; 2 -- index is invalid
*/
USBRL_API 
int CDECL usb_relay_device_open_one_relay_channel(intptr_t hHandle, int index);

/** Turn ON all relay channels on the USB-Relay-Device
@param hHandle -- which usb relay device your want to operate
@returns: 0 -- success; 1 -- error
*/
USBRL_API
int CDECL usb_relay_device_open_all_relay_channel(intptr_t hHandle);

/** Turn OFF a relay channel on the USB-Relay-Device
@param index -- which channel your want to close
@param hHandle -- which usb relay device your want to operate
@returns: 0 -- success; 1 -- error
*/
USBRL_API 
int CDECL usb_relay_device_close_one_relay_channel(intptr_t hHandle, int index);

/** Turn OFF all relay channels on the USB-Relay-Device
@param hHandle -- which usb relay device your want to operate
@returns: 0 -- success; 1 -- error; 2 -- index is invalid
*/
USBRL_API
int CDECL usb_relay_device_close_all_relay_channel(intptr_t hHandle);

/*
Status bits:  one bit indicate a relay status.
bit 0/1/2/3/4/5/6/7/8 indicate channel 1/2/3/4/5/6/7/8 status
Bit value 1 means ON, 0 means OFF.
@returns: 0 -- success; 1 -- error
*/
USBRL_API
int CDECL usb_relay_device_get_status(intptr_t hHandle, unsigned int *status);


#ifdef __cplusplus
}
#endif 

#endif /* USB_RELAY_DEVICE_H__ */