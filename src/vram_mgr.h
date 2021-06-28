#ifndef _OSL_VRAM_MGR_H_
#define _OSL_VRAM_MGR_H_

#ifdef __cplusplus
extern "C" {
#endif

#define OSL_VRAM_SIZE	(2 << 20)
#define OSL_VRAM_BASE	(0x40000000)
#define OSL_VRAM_END	(OSL_VRAM_BASE + OSL_VRAM_SIZE)

extern OSL_BOOL osl_useVramManager;
extern OSL_ADDR osl_currentVramPtr;

extern OSL_VOID oslVramMgrInit();
extern OSL_VOID_PTR oslVramMgrAllocBlock(OSL_SSIZE32 blockSize);
extern OSL_BOOL oslVramMgrFreeBlock(OSL_VOID_PTR blockAddress, OSL_SSIZE32 blockSize);
extern OSL_BOOL oslVramMgrSetParameters(OSL_VOID_PTR adrStart, OSL_SSIZE32 size);
#ifdef __cplusplus
}
#endif

#endif

