//=============================================================================
// Sample Application: Lighting (Per Fragment Phong)
//=============================================================================


// Entrega: Finalización OGL
// Integrantes: Carlos Camacho - Laura Rojas - Luis Martínez



#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include <iostream>
#include "glsl.h"
#include <time.h>
#include "glm.h"
#include <FreeImage.h> //*** Para Textura: Incluir librería
#include "Mundo.h"

//-----------------------------------------------------------------------------


class myWindow : public cwc::glutWindow
{
protected:
   cwc::glShaderManager SM;
   cwc::glShader *shader;
   cwc::glShader* shader1; //Para Textura: variable para abrir los shader de textura
   GLuint ProgramObject;
   clock_t time0,time1;
   float timer010;  // timer counting 0->1->0
   bool bUp;        // flag if counting up or down.
   GLMmodel* objmodel_ptr;
   GLMmodel* objmodel_ptr1; //*** Para Textura: variable para objeto texturizado
   GLuint texid; //*** Para Textura: variable que almacena el identificador de textura
   GLuint texid2; // Variable que almacena el identificador de la textura de las velas

   Mundo* mesaOctogonal;
   Mundo* alfombra;
   Mundo* chimenea;
   Mundo* sillas;
   Mundo* sillaconNino;
   Mundo* vela;
   Mundo* lampara;
   Mundo* cajon;
   Mundo* lampara2;

public:
	myWindow(){}

	//*** Para Textura: aqui adiciono un método que abre la textura en JPG
	void initialize_textures(void)
	{
		int w, h;
		GLubyte* data = 0;
		//data = glmReadPPM("soccer_ball_diffuse.ppm", &w, &h);
		//std::cout << "Read soccer_ball_diffuse.ppm, width = " << w << ", height = " << h << std::endl;

		//dib1 = loadImage("soccer_ball_diffuse.jpg"); //FreeImage

		
		// Textura de la alfombra
		glGenTextures(1, &texid);
		glBindTexture(GL_TEXTURE_2D, texid);
		glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		// Loading JPG file
		FIBITMAP* bitmap = FreeImage_Load(
			FreeImage_GetFileType("./Mallas/alfombra.jpg", 0),
			"./Mallas/alfombra.jpg");  //*** Para Textura: esta es la ruta en donde se encuentra la textura

		FIBITMAP* pImage = FreeImage_ConvertTo32Bits(bitmap);
		int nWidth = FreeImage_GetWidth(pImage);
		int nHeight = FreeImage_GetHeight(pImage);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidth, nHeight,
			0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));

		FreeImage_Unload(pImage);
		//
		glEnable(GL_TEXTURE_2D);


		// Textura de las velas
		glGenTextures(1, &texid2);
		glBindTexture(GL_TEXTURE_2D, texid2);
		glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		// Loading JPG file
		FIBITMAP* bitmap2 = FreeImage_Load(
			FreeImage_GetFileType("./Mallas/vela.jpg", 0),
			"./Mallas/vela.jpg");  //*** Para Textura: esta es la ruta en donde se encuentra la textura

		FIBITMAP* pImage2 = FreeImage_ConvertTo32Bits(bitmap2);
		int nWidth2 = FreeImage_GetWidth(pImage2);
		int nHeight2 = FreeImage_GetHeight(pImage2);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidth2, nHeight2,
			0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage2));

		FreeImage_Unload(pImage2);
		//
		glEnable(GL_TEXTURE_2D);

	}


	virtual void OnRender(void)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
      //timer010 = 0.09; //for screenshot!

      glPushMatrix();
	  glRotatef(timer010 * 30, 0.0, 1.0f, 0.0f);		//Rotación de la cámara

	  glTranslatef(0, 0, 2);
	  

      if (shader) shader->begin();

		  // Este es el llamado para dibujar los objetos en la escena sin textura
		  // Algunos objetos se rotaron para acomodarlos dentro de la escena

		  mesaOctogonal->objetosSinTextura(0.0f, -0.05f, 0.6f, 0.6);
		  glPushMatrix();
		  glRotatef(280, 0, 1, 0);
		  chimenea->objetosSinTextura(-0.8f, 0.15f, -0.12f, 2.5);
		  glPopMatrix();
		  glPushMatrix();
		  glRotatef(300, 0, 1, 0);
		  sillaconNino->objetosSinTextura(0.45f, 0.0f, 0.0f, 1.0);
		  glPopMatrix();
		  glPushMatrix();
		  glRotatef(170, 0, 1, 0);
		  sillas->objetosSinTextura(0.3f, 0.0f, -0.08f, 0.9);
		  glPopMatrix();
		  glPushMatrix();
		  glRotatef(280, 0, 1, 0);
		  cajon->objetosSinTextura(-0.8f, 0.67f, -0.12f, 2.3);
		  glPopMatrix();
		  glPushMatrix();
		  glRotatef(300, 0, 1, 0);
		  lampara->objetosSinTextura(-0.9f, 0.5f, 0.5f, 2);
		  glPopMatrix();
		  glPushMatrix();
		  glRotatef(-300, 0, 1, 0);
		  lampara2->objetosSinTextura(0.9f, 0.5f, 0.5f, 2);
		  glPopMatrix();
		  


	  /*glPushMatrix();
		  glTranslatef(0.0f, 0.0f, 0.0f);
		  glmDraw(objmodel_ptr, GLM_SMOOTH | GLM_MATERIAL);
		  glPopMatrix();
	      //glutSolidTeapot(1.0);*/
      if (shader) shader->end();

	  //*** Para Textura: llamado al shader para objetos texturizados
	  if (shader1) shader1->begin();

		  // Este es el llamado para dibujar los objetos con textura

		  alfombra->objetosTextura(0.0f, -0.15f, 0.0f, texid);
		  glPushMatrix();
		  vela->objetosTextura(0.0f, 0.03f, 0.6f, texid2);
		  glPopMatrix();


		  /*glPushMatrix();
		  //glRotatef(timer010 * 360, 0.5, 1.0f, 0.1f);
		  glTranslatef(0.0f, -0.1f, 0.0f);
		  glBindTexture(GL_TEXTURE_2D, texid);
		  glmDraw(objmodel_ptr1, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
		  glPopMatrix();*/
	  //glutSolidTeapot(1.0);
	  if (shader1) shader1->end(); 


      glutSwapBuffers();
      glPopMatrix();

      UpdateTimer();

		Repaint();
	}

	virtual void OnIdle() {}

	// When OnInit is called, a render context (in this case GLUT-Window) 
	// is already available!
	virtual void OnInit()
	{
		// Inicialización de cada uno de los objetos a usar en el mundo

		mesaOctogonal = new Mundo();
		alfombra = new Mundo();
		chimenea = new Mundo();
		sillas = new Mundo();
		sillaconNino = new Mundo();
		vela = new Mundo();
		cajon = new Mundo();
		lampara = new Mundo();
		lampara2 = new Mundo();

		glClearColor(0.5f, 0.5f, 1.0f, 0.0f);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);

		shader = SM.loadfromFile("vertexshader.txt","fragmentshader.txt"); // load (and compile, link) from file
		if (shader==0) 
         std::cout << "Error Loading, compiling or linking shader\n";
      else
      {
         ProgramObject = shader->GetProgramObject();
      }

	 //*** Para Textura: abre los shaders para texturas
		shader1 = SM.loadfromFile("vertexshaderT.txt", "fragmentshaderT.txt"); // load (and compile, link) from file
		if (shader1 == 0)
			std::cout << "Error Loading, compiling or linking shader\n";
		else
		{
			ProgramObject = shader1->GetProgramObject();
		}

      time0 = clock();
      timer010 = 0.0f;
      bUp = true;

	  // Llamado de cada objeto con su respectivo archivo .obj

	  mesaOctogonal->objetos("./Mallas/octogonal.obj");
	  alfombra->objetos("./Mallas/alfombra.obj");
	  chimenea->objetos("./Mallas/Chimenea.obj");
	  sillas->objetos("./Mallas/Silla.obj");
	  sillaconNino->objetos("./Mallas/ChinoSentado.obj");
	  vela->objetos("./Mallas/Vela.obj");
	  cajon->objetos("./Mallas/Cajon.obj");
	  lampara->objetos("./Mallas/Luz.obj");
	  lampara2->objetos("./Mallas/Luz.obj");

	  //Abrir mallas
	  /*objmodel_ptr = NULL;

	  if (!objmodel_ptr)
	  {
		  objmodel_ptr = glmReadOBJ("./Mallas/octogonal.obj");
		  if (!objmodel_ptr)
			  exit(0);

		  glmUnitize(objmodel_ptr);
		  glmFacetNormals(objmodel_ptr);
		  glmVertexNormals(objmodel_ptr, 90.0);
	  }


	  //*** Para Textura: abrir malla de objeto a texturizar
	  objmodel_ptr1 = NULL;

	  if (!objmodel_ptr1)
	  {
		  objmodel_ptr1 = glmReadOBJ("./Mallas/alfombra.obj");
		  if (!objmodel_ptr1)
			  exit(0);

		  glmUnitize(objmodel_ptr1);
		  glmFacetNormals(objmodel_ptr1);
		  glmVertexNormals(objmodel_ptr1, 90.0);
	  }
 */
	  //*** Para Textura: abrir archivo de textura
	  initialize_textures();
      //DemoLight();
	  
	}

	virtual void OnResize(int w, int h)
   {
      if(h == 0) h = 1;
	   float ratio = 1.0f * (float)w / (float)h;

      glMatrixMode(GL_PROJECTION);
	   glLoadIdentity();
	
	   glViewport(0, 0, w, h);

      gluPerspective(45,ratio,1,100);
	   glMatrixMode(GL_MODELVIEW);
	   glLoadIdentity();
	   gluLookAt(0.0f,0.0f,4.0f, 
		          0.0,0.0,-1.0,
			       0.0f,1.0f,0.0f);
   }
	virtual void OnClose(void){}
	virtual void OnMouseDown(int button, int x, int y){}    
	virtual void OnMouseUp(int button, int x, int y){}
	virtual void OnMouseWheel(int nWheelNumber, int nDirection, int x, int y){}

	virtual void OnKeyDown(int nKey, char cAscii)
	{       
		if (cAscii == 27) // 0x1b = ESC
		{
			this->Close(); // Close Window!
		} 
	};

	virtual void OnKeyUp(int nKey, char cAscii)
	{
      if (cAscii == 's')      // s: Shader
         shader->enable();
      else if (cAscii == 'f') // f: Fixed Function
         shader->disable();
	}

   void UpdateTimer()
   {
      time1 = clock();
      float delta = static_cast<float>(static_cast<double>(time1-time0)/static_cast<double>(CLOCKS_PER_SEC));
      delta = delta / 4;
      if (delta > 0.00005f)
      {
         time0 = clock();
         if (bUp)
         {
            timer010 += delta;
            if (timer010>=1.0f) { timer010 = 1.0f; bUp = false;}
         }
         else
         {
            timer010 -= delta;
            if (timer010<=0.0f) { timer010 = 0.0f; bUp = true;}
         }
      }
   }

   void DemoLight(void)
   {
	   glEnable(GL_LIGHTING);
	   glEnable(GL_LIGHT0);
	   glEnable(GL_NORMALIZE);
   }
};

//-----------------------------------------------------------------------------

class myApplication : public cwc::glApplication
{
public:
	virtual void OnInit() {std::cout << "Hello World!\n"; }
};

//-----------------------------------------------------------------------------

int main(void)
{
	myApplication*  pApp = new myApplication;
	myWindow* myWin = new myWindow();

	pApp->run();
	delete pApp;
	return 0;
}

//-----------------------------------------------------------------------------

