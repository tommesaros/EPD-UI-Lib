const uint32_t power_icon_width = 32;
const uint32_t power_icon_height = 32;
const uint8_t power_icon_data[(32*32)/2] = {
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0x0F, 0x00, 0x00, 0xF0, 0xFF, 0x00, 0x00, 0xFF, 0x0F, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 
	0xFF, 0xFF, 0x0F, 0x00, 0x00, 0xF0, 0xFF, 0x00, 0x00, 0xFF, 0x0F, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 
	0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0xFF, 0xFF, 
	0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 
	0xFF, 0x0F, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0xF0, 0xFF, 
	0xFF, 0x0F, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xF0, 0xFF, 
	0xFF, 0x0F, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xF0, 0xFF, 
	0xFF, 0x0F, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xF0, 0xFF, 
	0xFF, 0x0F, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xF0, 0xFF, 
	0xFF, 0x0F, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xF0, 0xFF, 
	0xFF, 0x0F, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xF0, 0xFF, 
	0xFF, 0x0F, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xF0, 0xFF, 
	0xFF, 0x0F, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xF0, 0xFF, 
	0xFF, 0x0F, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0xF0, 0xFF, 
	0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 
	0xFF, 0xFF, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0xFF, 0xFF, 
	0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 
	0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	};
