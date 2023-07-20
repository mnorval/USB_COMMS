//******************************************************************************
//
// File Version 1.01
//
//******************************************************************************

#include "Definit.h"
#include "VARs.h"

//******************************************************************************
// The number of bytes in each report,
// calculated from Report Size and Report Count in the report descriptor
//******************************************************************************
unsigned char const HID_INPUT_REPORT_BYTES      = 1;
unsigned char const HID_OUTPUT_REPORT_BYTES     = 1;

unsigned char const HID_FEATURE_REPORT_BYTES    = 2;
//******************************************************************************
// Byte constants
//******************************************************************************
unsigned char const NUM_ENDPOINTS               = 2;
unsigned char const ConfigDescr_wTotalLength    = USB_CONFIG_DESCRIPTOR_LEN + USB_INTERF_DESCRIPTOR_LEN + USB_HID_DESCRIPTOR_LEN + (NUM_ENDPOINTS * USB_ENDP_DESCRIPTOR_LEN);
unsigned char const HID_ReportDesc_len          = 47;

unsigned char const Low_HID_ReportDesc_len      = HID_ReportDesc_len;
unsigned char const High_HID_ReportDesc_len     = HID_ReportDesc_len >> 8;

unsigned char const Low_HID_PACKET_SIZE         = HID_PACKET_SIZE;
unsigned char const High_HID_PACKET_SIZE        = HID_PACKET_SIZE >> 8;



//******************************************************************************
// Descriptor Tables
//******************************************************************************
unsigned char const DescTables[USB_DEVICE_DESCRIPTOR_ALL_LEN*2] = {

// Device Descriptor
    USB_DEVICE_DESCRIPTOR_LEN, 0,           // bLength               - Length of Device descriptor (always 0x12)
    USB_DEVICE_DESCRIPTOR_TYPE, 0,          // bDescriptorType       - 1 = DEVICE descriptor
    0x00, 0,                                // bcdUSB                - USB revision 2.00 (low byte)
    0x02, 0,                                //                                           (high byte)
    0x00, 0,                                // bDeviceClass          - Zero means each interface operates independently (class code in the interface descriptor)
    0x00, 0,                                // bDeviceSubClass
    0x00, 0,                                // bDeviceProtocol
    EP0_PACKET_SIZE, 0,                     // bMaxPacketSize0       - maximum size of a data packet for a control transfer over EP0
    0x34, 0,                                // idVendor              - Vendor  ID (low byte)
    0x12, 0,                                //                                    (high byte)
    0x01, 0,                                // idProduct             - Product ID (low byte)
    0x00, 0,                                //                                    (high byte)
    0x01, 0,                                // bcdDevice             - ( low byte)
    0x00, 0,                                //                         (high byte)
    0x01, 0,                                // iManufacturer         - String1
    0x02, 0,                                // iProduct              - String2
    0x00, 0,                                // iSerialNumber         - ( None )
    0x01, 0,                                // bNumConfigurations    - 1

// Configuration Descriptor
    USB_CONFIG_DESCRIPTOR_LEN, 0,           // bLength               - Length of Configuration descriptor (always 0x09)
    USB_CONFIG_DESCRIPTOR_TYPE, 0,          // bDescriptorType       - 2 = CONFIGURATION descriptor
    ConfigDescr_wTotalLength, 0,            // wTotalLength          - Total length of this config. descriptor plus the interface and endpoint descriptors that are part of the configuration.
    0x00, 0,                                //                         ( high byte)
    0x01, 0,                                // bNumInterfaces        - Number of interfaces
    0x01, 0,                                // bConfigurationValue   - Configuration Value
    0x00, 0,                                // iConfiguration        - String Index for this configuration ( None )
    0xA0, 0,                                // bmAttributes          - attributes - "Bus powered" and "Remote wakeup"
    50, 0,                                  // MaxPower              - bus-powered draws 50*2 mA from the bus.

// Interface Descriptor
    USB_INTERF_DESCRIPTOR_LEN, 0,           // bLength               - Length of Interface descriptor (always 0x09)
    USB_INTERFACE_DESCRIPTOR_TYPE, 0,       // bDescriptorType       - 4 = INTERFACE descriptor
    0x00, 0,                                // bInterfaceNumber      - Number of interface, 0 based array
    0x00, 0,                                // bAlternateSetting     - Alternate setting
    NUM_ENDPOINTS, 0,                       // bNumEndPoints         - Number of endpoints used in this interface
    0x03, 0,                                // bInterfaceClass       - assigned by the USB
    0x00, 0,                                // bInterfaceSubClass    - Not A boot device
    0x00, 0,                                // bInterfaceProtocol    - none
    0x00, 0,                                // iInterface            - Index to string descriptor that describes this interface ( None )

// HID Descriptor
    USB_HID_DESCRIPTOR_LEN, 0,              // bLength               - Length of HID descriptor (always 0x09)
    USB_HID_DESCRIPTOR_TYPE, 0,             // bDescriptorType       - 0x21 = HID descriptor
    0x01, 0,                                // HID class release number (1.01)
    0x01, 0,
    0x00, 0,                                // Localized country code (none)
    0x01, 0,                                // # of HID class descriptor to follow (1)
    0x22, 0,                                // Report descriptor type (HID)
    Low_HID_ReportDesc_len, 0,
    High_HID_ReportDesc_len, 0,

// EP1_RX Descriptor
    USB_ENDP_DESCRIPTOR_LEN, 0,             // bLength               - length of descriptor (always 0x07)
    USB_ENDPOINT_DESCRIPTOR_TYPE, 0,        // bDescriptorType       - 5 = ENDPOINT descriptor
    0x81, 0,                                // bEndpointAddress      - In, EP1
    USB_ENDPOINT_TYPE_INTERRUPT, 0,         // bmAttributes          - Endpoint Type - Interrupt
    Low_HID_PACKET_SIZE, 0,                 // wMaxPacketSize        - max packet size - low order byte
    High_HID_PACKET_SIZE, 0,                //                       - max packet size - high order byte
    1, 0,                                  // bInterval             - polling interval (1 ms)

// EP1_TX Descriptor
    USB_ENDP_DESCRIPTOR_LEN, 0,             // bLength               - length of descriptor (always 0x07)
    USB_ENDPOINT_DESCRIPTOR_TYPE, 0,        // bDescriptorType       - 5 = ENDPOINT descriptor
    0x01, 0,                                // bEndpointAddress      - Out, EP1
    USB_ENDPOINT_TYPE_INTERRUPT, 0,         // bmAttributes          - Endpoint Type - Interrupt
    Low_HID_PACKET_SIZE, 0,                 // wMaxPacketSize        - max packet size - low order byte
    High_HID_PACKET_SIZE, 0,                //                       - max packet size - high order byte
    1, 0,                                  // bInterval             - polling interval (1 ms)

// HID_Report Descriptor
    0x06, 0,                                // USAGE_PAGE (Vendor Defined)
    0xA0, 0,
    0xFF, 0,
    0x09, 0,                                // USAGE ID (Vendor Usage 1)
    0x01, 0,
    0xA1, 0,                                // COLLECTION (Application)
    0x01, 0,
//  The Input report
    0x09, 0,                                // USAGE ID - Vendor defined
    0x03, 0,
    0x15, 0,                                //   LOGICAL_MINIMUM (0)
    0x00, 0,
    0x26, 0,                                //   LOGICAL_MAXIMUM (255)
    0x00, 0,
    0xFF, 0,
    0x75, 0,                                //   REPORT_SIZE (8)
    0x08, 0,
    0x95, 0,                                //   REPORT_COUNT (2)
    HID_INPUT_REPORT_BYTES, 0,
    0x81, 0,                                //   INPUT (Data,Var,Abs)
    0x02, 0,
//  The Output report
    0x09, 0,                                // USAGE ID - Vendor defined
    0x04, 0,
    0x15, 0,                                //   LOGICAL_MINIMUM (0)
    0x00, 0,
    0x26, 0,                                //   LOGICAL_MAXIMUM (255)
    0x00, 0,
    0xFF, 0,
    0x75, 0,                                //   REPORT_SIZE (8)
    0x08, 0,
    0x95, 0,                                //   REPORT_COUNT (2)
    HID_OUTPUT_REPORT_BYTES, 0,
    0x91, 0,                                //   OUTPUT (Data,Var,Abs)
    0x02, 0,
//  The Feature report
    0x09, 0,                                // USAGE ID - Vendor defined
    0x05, 0,
    0x15, 0,                                //   LOGICAL_MINIMUM (0)
    0x00, 0,
    0x26, 0,                                //   LOGICAL_MAXIMUM (255)
    0x00, 0,
    0xFF, 0,
    0x75, 0,                                //   REPORT_SIZE (8)
    0x08, 0,
    0x95, 0,                                //   REPORT_COUNT (2)
    HID_FEATURE_REPORT_BYTES, 0,
    0xB1, 0,                                //   FEATURE (Data,Var,Abs)
    0x02, 0,
//  End Collection
    0xC0, 0                                 // END_COLLECTION
};
//******************************************************************************
unsigned char const LangIDDescr[8] = {
    0x04, 0,
    USB_STRING_DESCRIPTOR_TYPE, 0,
    0x09, 0,                                // LangID (0x0409) - Low
    0x04, 0                                 //                 - High
};
//******************************************************************************
unsigned char const ManufacturerDescr[68] = {
    34, 0,
    USB_STRING_DESCRIPTOR_TYPE, 0,
    'm', 0, 0, 0,
    'i', 0, 0, 0,
    'k', 0, 0, 0,
    'r', 0, 0, 0,
    'o', 0, 0, 0,
    'E', 0, 0, 0,
    'l', 0, 0, 0,
    'e', 0, 0, 0,
    'k', 0, 0, 0,
    't', 0, 0, 0,
    'r', 0, 0, 0,
    'o', 0, 0, 0,
    'n', 0, 0, 0,
    'i', 0, 0, 0,
    'k', 0, 0, 0,
    'a', 0, 0, 0
};
//******************************************************************************
unsigned char const ProductDescr[96] = {
    48, 0,
    USB_STRING_DESCRIPTOR_TYPE, 0,
    'm', 0, 0, 0,
    'i', 0, 0, 0,
    'k', 0, 0, 0,
    'r', 0, 0, 0,
    'o', 0, 0, 0,
    'C', 0, 0, 0,
    ' ', 0, 0, 0,
    'H', 0, 0, 0,
    'I', 0, 0, 0,
    'D', 0, 0, 0,
    ' ', 0, 0, 0,
    'L', 0, 0, 0,
    'i', 0, 0, 0,
    'b', 0, 0, 0,
    'r', 0, 0, 0,
    'a', 0, 0, 0,
    'r', 0, 0, 0,
    'y', 0, 0, 0,
    ' ', 0, 0, 0,
    't', 0, 0, 0,
    'e', 0, 0, 0,
    's', 0, 0, 0,
    't', 0, 0, 0
};
//******************************************************************************
unsigned char const StrUnknownDescr[4] = {
    2, 0,
    USB_STRING_DESCRIPTOR_TYPE, 0
};
//******************************************************************************







//******************************************************************************
// Initialization Function
//******************************************************************************
void InitUSBdsc()
{
Byte_tmp_0[0] = NUM_ENDPOINTS;
Byte_tmp_0[0] = ConfigDescr_wTotalLength;
Byte_tmp_0[0] = HID_ReportDesc_len;
Byte_tmp_0[0] = Low_HID_ReportDesc_len;
Byte_tmp_0[0] = High_HID_ReportDesc_len;
Byte_tmp_0[0] = Low_HID_PACKET_SIZE;
Byte_tmp_0[0] = High_HID_PACKET_SIZE;


DescTables;

LangIDDescr;
ManufacturerDescr;
ProductDescr;
StrUnknownDescr;

}
//******************************************************************************
