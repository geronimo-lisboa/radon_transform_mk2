1)Por a GLEW e GLFW funcionando - Iniciado 20/07/2017, Terminado 20/07/2017

2)Carga do Shepp-Logan phantom e sua convers�o para 1 canal - Iniciado 21/07/2017, Terminado 21/07/2017

3)Cria��o da geometria na GPU e carga do phantom na GPU, com exibi��o na tela. - Iniciado 21/07/2017
22/07/2017 Apareceu na GPU.
24/07/2017 Feito

4)Render-To-Texture, para ver como �, com retorno da textura para a CPU.

5)A radon direta como no artigo, com as proje��es unidimensionais retornando pra CPU
5.1)Montar a 1a proje��o
5.2)Gerar todas as proje��es
5.3)Sinograma

A partir daqui fica mais nebuloso o que fazer... Tenho que fazer uma fourier transform, aplic�-la nas proje��es para realizar um certo filtro e gerar a imagem reconstru�da.

Links importantes:
https://www.youtube.com/watch?v=5Vyc1TzmNI8 Uma demonstra��o da aquisi��o dos dados do phantom, de como o tomografo pega os dados.
http://www.dspguide.com/ch25/5.htm Informa��es importantes sobre aquisi��o e reconstru��o de tomografias.
http://christian.mendl.net/software/radon_gpu_manuscript.pdf O artigo no qual me baseio.
http://www.cs.cmu.edu/~galeotti/methods_course/ITK_Filters2.pdf Sobre filtro, pro futuro.
http://duriansoftware.com/joe/An-intro-to-modern-OpenGL.-Chapter-2.1:-Buffers-and-Textures.html - Tutorial de opengl moderno.
http://antongerdelan.net/opengl/hellotriangle.html Muito melhor que o duriansoftware.
Observa��es:

1) Por copyAssets.bat nos eventos de build (ex: C:\programacao\radon_transform_mk2\copyAssets.bat)
2) Por enquanto uso AMD CodeXL (previously: gRemedy, gDEBugger) para depurar.