1)Por a GLEW e GLFW funcionando - Iniciado 20/07/2017, Terminado 20/07/2017

2)Carga do Shepp-Logan phantom e sua conversão para 1 canal - Iniciado 21/07/2017, Terminado 21/07/2017

3)Criação da geometria na GPU e carga do phantom na GPU, com exibição na tela. - Iniciado 21/07/2017

4)Render-To-Texture, para ver como é, com retorno da textura para a CPU.

5)A radon direta como no artigo, com as projeções unidimensionais retornando pra CPU


A partir daqui fica mais nebuloso o que fazer... Tenho que fazer uma fourier transform, aplicá-la nas projeções para realizar um certo filtro e gerar a imagem reconstruída.

Links importantes:
https://www.youtube.com/watch?v=5Vyc1TzmNI8 Uma demonstração da aquisição dos dados do phantom, de como o tomografo pega os dados.
http://www.dspguide.com/ch25/5.htm Informações importantes sobre aquisição e reconstrução de tomografias.
http://christian.mendl.net/software/radon_gpu_manuscript.pdf O artigo no qual me baseio.
http://www.cs.cmu.edu/~galeotti/methods_course/ITK_Filters2.pdf Sobre filtro, pro futuro.
http://duriansoftware.com/joe/An-intro-to-modern-OpenGL.-Chapter-2.1:-Buffers-and-Textures.html - Tutorial de opengl moderno.