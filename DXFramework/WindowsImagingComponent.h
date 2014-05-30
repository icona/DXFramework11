#pragma once

#include <memory>
#include <wincodec.h>
#include <wincodecsdk.h>

#pragma comment(lib, "WindowsCodecs.lib")

namespace wic
{
	std::shared_ptr<IWICImagingFactory> CreateWicFactory();
	std::shared_ptr<IWICBitmapDecoder> CreateDecoder(const TCHAR *path);
	std::shared_ptr<IWICBitmapFrameDecode> AccessFrame(IWICBitmapDecoder *dec);
	std::shared_ptr<IWICFormatConverter> CreateConverter();
};