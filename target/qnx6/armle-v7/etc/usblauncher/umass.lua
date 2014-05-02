-- Descriptor information for USB Mass Storage Device

USBDC_FULL_SPEED_MPS     = 64;
USBDC_HIGH_SPEED_MPS     = 512;

USBDC_VENDOR_ID          = 0xcbcb;
USBDC_PRODUCT_ID         = 0x5657;
USBDC_MAX_CURRENT        = 0;
USBDC_NUM_CONFIGURATIONS = 1;           -- must be 1
USBDC_REVISION           = 0x0200;

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

SIZE_CONFIG_DESC = (9 + 9 + 7 + 7)

fs_config_descriptor = {
	0x9,                    -- bLength
	0x2,                    -- bDescriptorType
	lsb(SIZE_CONFIG_DESC),  -- wLength (LSB)
	msb(SIZE_CONFIG_DESC),  -- wLength (MSB)
	0x1,                    -- bNumInterfaces
	0x1,                    -- bConfigurationValue
	0x0,                    -- iConfiguration
	0xC0,                   -- bmAttributes
	0x00,                   -- max power

-- Interface descriptor
	0x09,                   -- bLength
	0x04,                   -- bDescriptorType: interface
	0x00,                   -- bInterfaceNumber
	0x00,                   -- bAlternateSetting
	0x02,                   -- bNumEndpoints
	0x08,                   -- bInterfaceClass
	0x06,                   -- bInterfaceSubClass
	0x50,                   -- nInterfaceProtocol
	0x00,                   -- iInterface

-- Endpoint 1 Bulk In Descriptor
	0x07,                   -- bLength
	0x05,                   -- bDescriptorType
	0x81,                   -- bEndpointAddress
	0x02,                   -- bmAttributes
	0x40,                   -- wMaxPacketSize
	0x00,
	0x00,                   -- bInterval

-- Endpoint 2 Bulk Out Descriptor
	0x07,                   -- bLength
	0x05,                   -- bDescriptorType
	0x02,                   -- bEndpointAddress
	0x02,                   -- bmAttributes
	0x40,                   -- wMaxPacketSize
	0x00,
	0x00                    -- bInterval
};

hs_config_descriptor = {
	0x9,                                -- bLength
	0x2,                                -- bDescriptorType
	lsb(SIZE_CONFIG_DESC),              -- wLength (LSB)
	msb(SIZE_CONFIG_DESC),              -- wLength (MSB)
	0x1,                                -- bNumInterfaces
	0x1,                                -- bConfigurationValue
	0x0,                                -- iConfiguration
	0xC0,                               -- bmAttributes
	0x00,                               -- max power

-- Interface descriptor
	0x09,                               -- bLength
	0x04,                               -- bDescriptorType: Interface
	0x00,                               -- bInterfaceNumber
	0x00,                               -- bAlternateSetting
	0x02,                               -- bNumEndpoints
	0x08,                               -- bInterfaceClass
	0x06,                               -- bInterfaceSubClass
	0x50,                               -- nInterfaceProtocol
	0x00,                               -- iInterface

-- Endpoint 1 Bulk In Descriptor
	0x07,                               -- bLength
	0x05,                               -- bDescriptorType
	0x81,                               -- bEndpointAddress
	0x02,                               -- bmAttributes
	lsb(USBDC_HIGH_SPEED_MPS),          -- wMaxPacketSize (2 bytes)
	msb(USBDC_HIGH_SPEED_MPS),
	0x00,                               -- bInterval

-- Endpoint 2 Bulk Out Descriptor
	0x07,                               -- bLength
	0x05,                               -- bDescriptorType
	0x02,                               -- bEndpointAddress
	0x02,                               -- bmAttributes
	lsb(USBDC_HIGH_SPEED_MPS),          -- wMaxPacketSize (2 bytes)
	msb(USBDC_HIGH_SPEED_MPS),
	0x00                                -- bInterval
};

string_descriptors = {
	{
-- Language Code Descriptor
		0x04,                               -- bLength
		0x03,                               -- bDescriptorType
		0x09,                               -- wLANGID (LSB)
		0x04,                               -- wLANGIF (MSB)
	},
	'QNX Software Systems',
	'USB Mass Storage Test Device',
	'123456789ABC'
};
