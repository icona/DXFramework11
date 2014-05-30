#pragma once

#include "WindowsImagingComponent.h"
#include "ReleaseIUnknown.h"

std::shared_ptr<IWICImagingFactory> wic::CreateWicFactory()
{
	IWICImagingFactory *factory = nullptr;
	auto hr = ::CoCreateInstance(
		CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (void**)&factory
		);
	if (FAILED(hr)) throw;
	return std::shared_ptr<IWICImagingFactory>(factory, ReleaseIUnknown);
}

std::shared_ptr<IWICBitmapDecoder> wic::CreateDecoder(const TCHAR *path)
{
	IWICBitmapDecoder *dec = nullptr;
	auto hr = CreateWicFactory()->CreateDecoderFromFilename(
		path, NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &dec
		);

	if (FAILED(hr)) throw;
	return std::shared_ptr<IWICBitmapDecoder>(dec, ReleaseIUnknown);
}

std::shared_ptr<IWICBitmapFrameDecode> wic::AccessFrame(IWICBitmapDecoder *dec)
{
	IWICBitmapFrameDecode *frame = nullptr;
	if (FAILED(dec->GetFrame(0, &frame))) throw;
	return std::shared_ptr<IWICBitmapFrameDecode>(frame, ReleaseIUnknown);
}

std::shared_ptr<IWICFormatConverter> wic::CreateConverter()
{
	IWICFormatConverter *converter = nullptr;
	auto hr = CreateWicFactory()->CreateFormatConverter(&converter);
	if (FAILED(hr)) throw;
	return std::shared_ptr<IWICFormatConverter>(converter, ReleaseIUnknown);
}
