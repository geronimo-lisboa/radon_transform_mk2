#ifndef __myImageLoader_hxx
#define __myImageLoader_hxx

#include "myImageLoader.h"
#include "itkObjectFactory.h"
#include "itkImageRegionIterator.h"
#include "itkImageRegionConstIterator.h"
#include <itkImageFileReader.h>
#include <itkImage.h>
namespace itk
{
	template< class TImage>
	void myImageLoader< TImage>::GenerateData()
	{
		if (m_FileName == "") throw itk::ExceptionObject("Must inform the filename");
		//Carga do arquivo
		typedef itk::Image<FixedArray<unsigned char, 4>, 2> LoadedImageType;
		typedef itk::ImageFileReader<LoadedImageType> ReaderType;
		ReaderType::Pointer reader = ReaderType::New();
		reader->SetFileName(m_FileName.c_str());
		reader->Update();
		LoadedImageType::Pointer loadedMultichannelImage = reader->GetOutput();
		//Conversão pra 1 canal


		//typename TOutputImage::Pointer output = this->GetOutput();
		//typename TOutputImage::RegionType region;
		//typename TOutputImage::IndexType start;
		//start[0] = 0;
		//start[1] = 0;

		//typename TOutputImage::SizeType size;
		//size[0] = 200;
		//size[1] = 300;

		//region.SetSize(size);
		//region.SetIndex(start);

		//output->SetRegions(region);
		//output->Allocate();

		//itk::ImageRegionIterator<TOutputImage> imageIterator(output, output->GetLargestPossibleRegion());

		//while (!imageIterator.IsAtEnd())
		//{
		//	if (imageIterator.GetIndex()[0] == imageIterator.GetIndex()[1])
		//	{
		//		imageIterator.Set(255);
		//	}
		//	else
		//	{
		//		imageIterator.Set(0);
		//	}

		//	++imageIterator;
		//}
	}

}// end namespace


#endif