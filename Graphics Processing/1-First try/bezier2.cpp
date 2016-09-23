#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#define f(a,b,c) for(int a=b;a<c;a++)
#define frg(a,b) for(int a=adj[b];~a;a=ant[a])
typedef long long ll;
std::vector<std::pair<double,double> > v,curv;
long long coeficientesFixos[10000];//equivalente ao binomio de newton
double t,subT;//t=t do ponto atual, subT= 1-t, do ponto atual
double tArr[10000],subTArr[10000];//array que guarda as potencias


void display() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer
  glLineWidth(0.5);
glColor3f(1.0, 1.0, 1.0);
glBegin(GL_LINES);
glVertex2f(1.0f,0.0f);
glVertex2f(-1.0f,0.0f);
glEnd();
glFlush();
glLineWidth(0.5);
glColor3f(1.0, 1.0, 1.0);
glBegin(GL_LINES);
glVertex2f(0.0f,1.0f);
glVertex2f(0.0f,-1.0f);
glEnd();
glFlush();
  for(int i=0;i<v.size()-1;i++){
   glLineWidth(1.5);
glColor3f(0.0, 1.0, 0.0);
glBegin(GL_LINES);
glVertex2f(float(v[i].first)/5.0,float(v[i].second)/5.0);
glVertex2f(float(v[i+1].first)/5.0, float(v[i+1].second)/5.0);
glEnd();
glFlush(); 
   }
   // Draw a Red 1x1 Square centered at origin
   for(int i=0;i<curv.size()-1;i++){
   glLineWidth(2.5);
glColor3f(1.0, 0.0, 0.0);
glBegin(GL_LINES);
glVertex2f(float(curv[i].first)/5.0,float(curv[i].second)/5.0);
glVertex2f(float(curv[i+1].first)/5.0, float(curv[i+1].second)/5.0);
glEnd();
glFlush(); 
   }
   glFlush();  // Render now
}


int main(int argc, char** argv){//Geraçao de Bezier em O(N^2+NP) por bernstein, em contraste com a geraçao em O(N^2*P) feita por de casteljau
	int p,n;double a,b;//p= numero de pontos gerados,n=numeros de pontos que caracterizam a curva
	std::cout<<"Digite os numero de pontos\n";
	scanf("%d",&n);p=100;
	std::cout<<"digite os pontos\n";
	for(int i=0;i<n;i++){
		scanf("%lf%lf",&a,&b);
		v.push_back(std::make_pair(a,b));
	}
	coeficientesFixos[1]=1;
	for(int i=1;i<n;i++){//O(N^2), para gerar os binomios de newton
		for(int j=i+1;j>=1;j--){
			coeficientesFixos[j]=coeficientesFixos[j]+coeficientesFixos[j-1];
		}
	}p--;
	tArr[0]=subTArr[0]=1;
	for(int i=0;i<=p;i++){//O(P*N)
		t=double(i)/double(p);
		subT=1-t;
		for(int j=1;j<n;j++){//Preprocessando potencias em O(N)
			tArr[j]=t*tArr[j-1];
			subTArr[j]=subT*subTArr[j-1];
		}
		a=b=0;
		for(int j=0;j<n;j++){//fazendo a formula em O(N)
			a+=tArr[j]*subTArr[n-j-1]*double(coeficientesFixos[j+1])*v[j].first;
			b+=tArr[j]*subTArr[n-j-1]*double(coeficientesFixos[j+1])*v[j].second;
		}
		curv.push_back(std::make_pair(a,b));
	}


	glutInit(&argc, argv);                 // Initialize GLUT
   glutCreateWindow("OpenGL Setup Test"); // Create a window with the given title
   glutInitWindowSize(320, 320);   // Set the window's initial width & height
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
   glutDisplayFunc(display); // Register display callback handler for window re-paint
   glutMainLoop(); 


}
