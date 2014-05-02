--  Descriptor information for iAP2 NCM Accessory Device

USBDC_FULL_SPEED_MPS     = 64;
USBDC_HIGH_SPEED_MPS     = 512;

USBDC_VENDOR_ID          = 0xabab;
USBDC_PRODUCT_ID         = 0x5656;
USBDC_MAX_CURRENT        = 0;
USBDC_NUM_CONFIGURATIONS = 1;           -- must be 1
USBDC_REVISION           = 0x0200;

NCM_SEG_LEN              = 8192;

device_descriptor  = {
	0x12,                               -- bLength
	0x01,                               -- bDescriptorType
	0x00,                               -- bcdUSB (LSB)
	0x02,                               -- bcdUSB (MSB)
	0x00,                               -- bDeviceClass
	0x00,                               -- bDeviceSubClass
	0x00,                               -- bDeviceProtocol
	0x40,                               -- bMaxPacketSize
	lsb(USBDC_VENDOR_ID),               -- idVendor (LSB)
	msb(USBDC_VENDOR_ID),               -- idVendor (MSB)
	lsb(USBDC_PRODUCT_ID),              -- idProduct (LSB)
	msb(USBDC_PRODUCT_ID),              -- idProduct (MSB)
	lsb(USBDC_REVISION),                -- bcdDevice (LSB)
	msb(USBDC_REVISION),                -- bcdDevice (MSB)
	0x01,                               -- iManufacture
	0x02,                               -- iProduct
	0x03,                               -- iSerialNumber
	USBDC_NUM_CONFIGURATIONS            -- bNumConfigurations
};

SIZE_CONFIG_DESC = (0x9 + 4*0x9 + 6 * 0x7 + 0x5 + 0x5 + 0xD + 0x6);  -- config_len + total_interfaces * interface_len + total_endpoints * endpoint_len

fs_config_descriptor = {
	0x09,                               -- bLength
	0x02,                               -- bDescriptorType
	lsb(SIZE_CONFIG_DESC),              -- wTotalLength (LSB)
	msb(SIZE_CONFIG_DESC),              -- wTotalLength (MSB)
	0x03,                               -- bNumInterfaces
	0x01,                               -- bConfigurationValue
	0x04,                               -- iConfiguration
	0x40,                               -- bmAttributes
	USBDC_MAX_CURRENT,                  -- max power

-- iAP2 interface descriptor
	0x09,                               -- bLength
	0x04,                               -- bDescriptorType
	0x00,                               -- bInterfaceNumber
	0x00,                               -- bAlternateSetting
	0x03,                               -- bNumEndpoints
	0xFF,                               -- bInterfaceClass
	0xF0,                               -- bInterfaceSubClass
	0x00,                               -- nInterfaceProtocol
	0x05,                               -- iInterface

-- Endpoint 1 Interrupt In
	0x07,                               -- bLength
	0x05,                               -- bDescriptorType
	0x81,                               -- bEndpointAddress
	0x03,                               -- bmAttributes
	0x40,                               -- wMaxPacketSize (LSB)
	0x00,                               -- wMaxPacketSize (MSB)
	0x04,                               -- bInterval: iAP2 spec requires 4ms->32ms

-- Endpoint 2 Bulk In Descriptor
	0x07,                               -- bLength
	0x05,                               -- bDescriptorType
	0x82,                               -- bEndpointAddress
	0x02,                               -- bmAttributes
	lsb(USBDC_FULL_SPEED_MPS),          -- wMaxPacketSize (LSB)
	msb(USBDC_FULL_SPEED_MPS),          -- wMaxPacketSize (MSB)
	0x00,                               -- bInterval

-- Endpoint 3 Bulk Out Descriptor
	0x07,                               -- bLength
	0x05,                               -- bDescriptorType
	0x03,                               -- bEndpointAddress
	0x02,                               -- bmAttributes
	lsb(USBDC_FULL_SPEED_MPS),          -- wMaxPacketSize (LSB)
	msb(USBDC_FULL_SPEED_MPS),          -- wMaxPacketSize (MSB)
	0x00,                               -- bInterval

-- CDC Network Control Model (NCM) interface Descriptor
	0x09,                               -- bLength
	0x04,                               -- bDescriptorType
	0x01,                               -- bInterfaceNumber
	0x00,                               -- bAlternateSetting
	0x01,                               -- bNumEndpoints
	0x02,                               -- bInterfaceClass
	0x0D,                               -- bInterfaceSubClass
	0x00,                               -- nInterfaceProtocol
	0x06,                               -- iInterface

-- USB Communication Class Header Functional Descriptor
	0x05,                               -- bLength
	0x24,                               -- bDescriptorType
	0x00,                               -- bDescriptorSubType
	0x10,                               -- bcdCDC (LSB)
	0x01,                               -- bcdCDC (MSB)

-- USB Communication Class Union Functional Descriptor
	0x05,                               -- bLength
	0x24,                               -- bDescriptorType
	0x06,                               -- bDescriptorSubType
	0x01,                               -- bControlInterface
	0x02,                               -- bSubordinateInterface0

-- USB Communication Class Ethernet Networking Functional Descriptor
	0x0D,                               -- bLength
	0x24,                               -- bDescriptorType
	0x0F,                               -- bDescriptorSubType
	0x08,                               -- iMACAddress
	0x00,                               -- bmEthernetStatistics
	0x00,
	0x00,
	0x00,
	lsb(NCM_SEG_LEN),                   -- wMaxSegmentSize (LSB)
	msb(NCM_SEG_LEN),                   -- wMaxSegmentSize (MSB)
	0x00,                               -- wNumberMCFilters (LSB)
	0x00,                               -- wNumberMCFilters (MSB)
	0x00,                               -- bNumberPowerFilters

-- USB Communication Class NCM Functional Descriptor
	0x06,                               -- bLength
	0x24,                               -- bDescriptorType
	0x1A,                               -- bDescriptorSubType
	0x00,                               -- bcdNcmVersion (LSB)
	0x01,                               -- bcdNcmVersion (MSB)
	0x00,                               -- bmNetworkCapabilities

-- Endpoint 1 Interrupt In
	0x07,                               -- bLength
	0x05,                               -- bDescriptorType
	0x84,                               -- bEndpointAddress
	0x03,                               -- bmAttributes
	lsb(USBDC_FULL_SPEED_MPS),          -- wMaxPacketSize (LSB)
	msb(USBDC_FULL_SPEED_MPS),          -- wMaxPacketSize (MSB)
	0x01,                               -- bInterval

-- CDC Network Data interface Descriptor  - Alternate 0
	0x09,                               -- bLength
	0x04,                               -- bDescriptorType
	0x02,                               -- bInterfaceNumber
	0x00,                               -- bAlternateSetting
	0x00,                               -- bNumEndpoints
	0x0A,                               -- bInterfaceClass
	0x00,                               -- bInterfaceSubClass
	0x01,                               -- nInterfaceProtocol
	0x07,                               -- iInterface

-- CDC Network Data interface Descriptor  - Alternate 1
	0x09,                               -- bLength
	0x04,                               -- bDescriptorType
	0x02,                               -- bInterfaceNumber
	0x01,                               -- bAlternateSetting
	0x02,                               -- bNumEndpoints
	0x0A,                               -- bInterfaceClass
	0x00,                               -- bInterfaceSubClass
	0x01,                               -- nInterfaceProtocol
	0x07,                               -- iInterface

-- Endpoint 1 Bulk In Descriptor
	0x07,                               -- bLength
	0x05,                               -- bDescriptorType
	0x85,                               -- bEndpointAddress
	0x02,                               -- bmAttributes
	lsb(USBDC_FULL_SPEED_MPS),          -- wMaxPacketSize (LSB)
	msb(USBDC_FULL_SPEED_MPS),          -- wMaxPacketSize (MSB)
	0x00,                               -- bInterval

-- Endpoint 2 Bulk Out Descriptor
	0x07,                               -- bLength
	0x05,                               -- bDescriptorType
	0x06,                               -- bEndpointAddress
	0x02,                               -- bmAttributes
	lsb(USBDC_FULL_SPEED_MPS),          -- wMaxPacketSize (LSB)
	msb(USBDC_FULL_SPEED_MPS),          -- wMaxPacketSize (MSB)
	0x00,                               -- bInterval
};

hs_config_descriptor = {
	0x09,                               -- bLength
	0x02,                               -- bDescriptorType
	lsb(SIZE_CONFIG_DESC),              -- wTotalLength (LSB)
	msb(SIZE_CONFIG_DESC),              -- wTotalLength (MSB)
	0x03,                               -- bNumInterfaces
	0x01,                               -- bConfigurationValue
	0x04,                               -- iConfiguration
	0x40,                               -- bmAttributes
	USBDC_MAX_CURRENT,                  -- max power

-- iAP2 Interface descriptor
	0x09,                               -- bLength
	0x04,                               -- bDescriptorType
	0x00,                               -- bInterfaceNumber
	0x00,                               -- bAlternateSetting
	0x03,                               -- bNumEndpoints
	0xFF,                               -- bInterfaceClass
	0xF0,                               -- bInterfaceSubClass
	0x00,                               -- nInterfaceProtocol
	0x05,                               -- iInterface

-- Endpoint 1 Interrupt In
	0x07,                               -- bLength
	0x05,                               -- bDescriptorType
	0x81,                               -- bEndpointAddress
	0x03,                               -- bmAttributes
	0x40,                               -- wMaxPacketSize (LSB)
	0x00,                               -- wMaxPacketSize (MSB)
	0x06,                               -- bInterval: iAP2 spec requires 4ms->32ms

-- Endpoint 2 Bulk In Descriptor
	0x07,                               -- bLength
	0x05,                               -- bDescriptorType
	0x82,                               -- bEndpointAddress
	0x02,                               -- bmAttributes
	lsb(USBDC_HIGH_SPEED_MPS),          -- wMaxPacketSize (LSB)
	msb(USBDC_HIGH_SPEED_MPS),          -- wMaxPacketSize (MSB)
	0x00,                               -- bInterval

-- Endpoint 3 Bulk Out Descriptor
	0x07,                               -- bLength
	0x05,                               -- bDescriptorType
	0x03,                               -- bEndpointAddress
	0x02,                               -- bmAttributes
	lsb(USBDC_HIGH_SPEED_MPS),          -- wMaxPacketSize (LSB)
	msb(USBDC_HIGH_SPEED_MPS),          -- wMaxPacketSize (MSB)
	0x00,                               -- bInterval

-- CDC Network Control Model (NCM) interface Descriptor
	0x09,                               -- bLength
	0x04,                               -- bDescriptorType
	0x01,                               -- bInterfaceNumber
	0x00,                               -- bAlternateSetting
	0x01,                               -- bNumEndpoints
	0x02,                               -- bInterfaceClass
	0x0D,                               -- bInterfaceSubClass
	0x00,                               -- nInterfaceProtocol
	0x06,                               -- iInterface

-- USB Communication Class Header Functional Descriptor
	0x05,                               -- bLength
	0x24,                               -- bDescriptorType
	0x00,                               -- bDescriptorSubType
	0x10,                               -- bcdCDC (LSB)
	0x01,                               -- bcdCDC (MSB)

-- USB Communication Class Union Functional Descriptor
	0x05,                               -- bLength
	0x24,                               -- bDescriptorType
	0x06,                               -- bDescriptorSubType
	0x01,                               -- bControlInterface
	0x02,                               -- bSubordinateInterface0

-- USB Communication Class Ethernet Networking Functional Descriptor
	0x0D,                               -- bLength
	0x24,                               -- bDescriptorType
	0x0F,                               -- bDescriptorSubType
	0x08,                               -- iMACAddress
	0x00,                               -- bmEthernetStatistics
	0x00,
	0x00,
	0x00,
	lsb(NCM_SEG_LEN),                   -- wMaxSegmentSize (LSB)
	msb(NCM_SEG_LEN),                   -- wMaxSegmentSize (MSB)
	0x00,                               -- wNumberMCFilters (LSB)
	0x00,                               -- wNumberMCFilters (MSB)
	0x00,                               -- bNumberPowerFilters

-- USB Communication Class NCM Functional Descriptor
	0x06,                               -- bLength
	0x24,                               -- bDescriptorType
	0x1A,                               -- bDescriptorSubType
	0x00,                               -- bcdNcmVersion (LSB)
	0x01,                               -- bcdNcmVersion (MSB)
	0x00,                               -- bmNetworkCapabilities

-- Endpoint 1 Interrupt In
	0x07,                               -- bLength
	0x05,                               -- bDescriptorType
	0x84,                               -- bEndpointAddress
	0x03,                               -- bmAttributes
	0x40,                               -- wMaxPacketSize (LSB)
	0x00,                               -- wMaxPacketSize (MSB)
	0x01,                               -- bInterval

-- CDC Network Data interface Descriptor
	0x09,                               -- bLength
	0x04,                               -- bDescriptorType
	0x02,                               -- bInterfaceNumber
	0x00,                               -- bAlternateSetting
	0x00,                               -- bNumEndpoints
	0x0A,                               -- bInterfaceClass
	0x00,                               -- bInterfaceSubClass
	0x01,                               -- nInterfaceProtocol
	0x07,                               -- iInterface

-- CDC Network Data interface Descriptor
	0x09,                               -- bLength
	0x04,                               -- bDescriptorType
	0x02,                               -- bInterfaceNumber
	0x01,                               -- bAlternateSetting
	0x02,                               -- bNumEndpoints
	0x0A,                               -- bInterfaceClass
	0x00,                               -- bInterfaceSubClass
	0x01,                               -- nInterfaceProtocol
	0x07,                               -- iInterface

-- Endpoint 1 Bulk In Descriptor
	0x07,                               -- bLength
	0x05,                               -- bDescriptorType
	0x85,                               -- bEndpointAddress
	0x02,                               -- bmAttributes
	lsb(USBDC_HIGH_SPEED_MPS),          -- wMaxPacketSize (LSB)
	msb(USBDC_HIGH_SPEED_MPS),          -- wMaxPacketSize (MSB)
	0x00,                               -- bInterval

-- Endpoint 2 Bulk Out Descriptor
	0x07,                               -- bLength
	0x05,                               -- bDescriptorType
	0x06,                               -- bEndpointAddress
	0x02,                               -- bmAttributes
	lsb(USBDC_HIGH_SPEED_MPS),          -- wMaxPacketSize (LSB)
	msb(USBDC_HIGH_SPEED_MPS),          -- wMaxPacketSize (MSB)
	0x00,                               -- bInterval
};

string_descriptors = {
	{
-- Language Code Descriptor
		0x04,                               -- bLength
		0x03,                               -- bDescriptorType
		0x09,                               -- wLANGID (LSB)
		0x04,                               -- wLANGIF (MSB)
	},

-- Manufacturer String Descriptor
	'QNX Software Systems',

-- Product String Descriptor
	'iAP2 NCM Accessory',

-- Serial String Descriptor
	'ABC-0123456789',

-- Configuration String Descriptor
	'Default Configuration',

-- iAP Interface Descriptor
	'iAP Interface',   -- must not change

-- CDC Network Control Model (NCM)
	'CDC Network Module (NCM)',

-- CDC Network Data
	'CDC Network Data',

-- MAC Address
	'001122334455'
};
