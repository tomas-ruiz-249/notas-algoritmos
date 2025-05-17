#include "red_social.cpp"

int main(){
    srand(time(0));
    GrafoSocial g;
    g.generarGrafo();
    g.most_connected();
}