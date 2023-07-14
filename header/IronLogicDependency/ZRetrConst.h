#pragma once

#define ZRS_MAX_DEV			8
#define ZRS_SEARCH_PORT		9000
#define ZRS_SEARCH_REQ		"SEEK Z397IP"

// Тип устройства
enum ZDEV_TYPE
{
	ZDT_UNDEF = 0,
	ZDT_Z397,			// Z-397
	ZDT_Z397_G_NORM,	// Z-397 Guard в режиме "Normal"
	ZDT_Z397_G_ADV,		// Z-397 Guard в режиме "Advanced"
	ZDT_Z2U,			// Z-2 USB
	ZDT_M3A,			// Matrix III Rd-All
	ZDT_Z2M,			// Z-2 USB MF
	ZDT_M3N,			// Matrix III Net
	ZDT_CPZ2MF,			// CP-Z-2MF
	ZDT_Z2EHR			// Z-2 EHR
};

