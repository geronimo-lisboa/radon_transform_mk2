#ifndef __myImageLoader_h
#define __myImageLoader_h

#include <itkImageSource.h>
#include <string>
namespace itk
{
	/*
	Carrega a imagem da forma como eu quero.
	Muitas das imagens que eu vou usar ser�o geradas pelo paint.net. Ele grava como multicanal mesmo quando � tudo cinza. Ent�o eu preciso
	remover os multicanais e aproveito que j� estou mexendo na imagem para fazer com que seus valores fiquem entre zero e um. Ent�o essa
	classe carrega a imagem, a converte para lumin�ncia via RGBToLuminanceImageFilter e depois p�e os escalares entre 0 e 1.
	Se a imagem j� for em tom de cinza po-la como lumin�ncia n�o mudar� muita coisa. Se for colorida, vai mudar. Como meu foco � imagens
	m�dicas que s�o tons de cinza isso n�o me importa de maneira alguma.
	*/
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