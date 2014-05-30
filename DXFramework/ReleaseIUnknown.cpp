#include "ReleaseIUnknown.h"

void ReleaseIUnknown(IUnknown *p)
{
	p->Release();
}
