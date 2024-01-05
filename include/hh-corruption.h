#ifndef _HH_CORRUPTION_H
#define _HH_CORRUPTION_H

int hhCorruptedBefore(struct hhMemoryBlockHeader *block);
int hhCorruptedAfter(struct hhMemoryBlockHeader *block);

#endif /*_HH_CORRUPTION_H*/