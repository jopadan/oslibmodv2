#ifndef _OSL_VRAM_MGR_H_
#define _OSL_VRAM_MGR_H_

#ifdef __cplusplus
extern "C" {
#endif

#define OSL_VRAM_SIZE	(2 << 20)
#define OSL_VRAM_BASE	(0x40000000)
#define OSL_VRAM_END	(OSL_VRAM_BASE + OSL_VRAM_SIZE)

#define OSL_VRAM_PERM	0xffff
#define OSL_MAX_VRAMMEM	200
#define OSL_VRAM_CACHE_FAILED 0xffff

typedef struct {
	void* imgptr;
	void* dcmpptr;
	uint16_t count;
	uint16_t decomp;
	uint8_t* dict;
} OSL_VRAMMEM;

extern int osl_useVramManager;
extern uintptr_t osl_currentVramPtr;

extern void oslVramMgrInit();
extern void *oslVramMgrAllocBlock(int blockSize);
extern int oslVramMgrFreeBlock(void *blockAddress, int blockSize);
extern int oslVramMgrSetParameters(void *adrStart, int size);
extern void oslVramFlush();
extern void oslVram
#ifdef __cplusplus
}
#endif

#endif

