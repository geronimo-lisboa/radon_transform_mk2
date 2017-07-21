#ifndef __myImageLoader_h
#define __myImageLoader_h

#include <itkImageSource.h>
#include <string>
namespace itk
{
	template< class TImage>
	class myImageLoader :public ImageSource< TImage >
	{
	public:
		/** Standard class typedefs. */
		typedef myImageLoader         Self;
		typedef ImageSource< TImage > Superclass;
		typedef SmartPointer< Self >  Pointer;
		/** Method for creation through the object factory. */
		itkNewMacro(Self);
		/** Run-time type information (and related methods). */
		itkTypeMacro(myImageLoader, ImageSource);

		itkSetMacro(FileName, std::string);
	protected:
		myImageLoader(){
			m_FileName = "";
		}
		~myImageLoader(){}

		/** Does the real work. */
		virtual void GenerateData();
	private:
		myImageLoader(const Self &); //purposely not implemented
		void operator=(const Self &);  //purposely not implemented
		std::string m_FileName;
	};
} //namespace ITK


#ifndef ITK_MANUAL_INSTANTIATION
#include "myImageLoader.cpp"
#endif


#endif // __itkImageFilter_h