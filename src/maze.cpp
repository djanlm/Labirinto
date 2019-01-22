#include <iostream>   // cout, cin, endl
#include <utility>    // std::pair<>
#include <random>     // radom_device, mt19937, std::shuffle.
#include <string>     // std::string
#include <cassert>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include "../include/DisjSets.h"
#include <stack>      // std::stack

//using namespace std;

int numeroAleatorio(int menor, int maior) {
       return rand()%(maior-menor+1) + menor;
}

void drawMaze(int altura, int largura, unsigned char Maze[], unsigned char TopWall,unsigned char RightWall, unsigned char BottomWall, unsigned char LeftWall){
    system("clear");
    for(int i=0; i<altura; i++){
        for(int j=largura*i; j<largura*i+largura; j++){
            if(Maze[j] & TopWall){
               std::cout<< "####";
            }else{std::cout<< "#  #";}
        }
        std::cout<<std::endl;
        for(int j=largura*i; j<largura*i+largura; j++){
            if(Maze[j] & LeftWall){
               std::cout<< "# ";
            }else{ std::cout<< "  ";}
            if(Maze[j] & RightWall){
               std::cout<< " #";
            }else{std::cout<< "  ";  }
        }
        std::cout<<std::endl;
        for(int j=largura*i; j<largura*i+largura; j++){
            if(Maze[j] & BottomWall){
               std::cout<< "####";
            }else{std::cout<< "#  #";}
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}

int main (int argc, char** argv){
    unsigned char TopWall = 1;
    unsigned char RightWall = 2;
    unsigned char BottomWall = 4;
    unsigned char LeftWall = 8;
    unsigned char trackedPath = 16;
    unsigned char wrongTrackedPath = 32;
    std::vector<int> v; //arMazena os números embaralhados aleatoreamente
    int altura=20;
    int largura=33;
    bool valido=false; //indica se o labirinto será valido ou totalmente conexo

    if(argc>4){
        std::cout<<"Há argumentos demais"<<std::endl;
        return 0;
    }
    else if(argc==4){
        if(isdigit(argv[1][0])){
            altura=atoi(argv[1]);
            if(isdigit(argv[2][0])){
                largura=atoi(argv[2]);
                valido=true;
            }else{
                valido=true;
                largura=atoi(argv[3]);
            }
        }else {
            valido=true;
            altura=atoi(argv[2]);
            largura=atoi(argv[3]);
        }
    }else if(argc==3){
         if(isdigit(argv[1][0])){
             altura=atoi(argv[1]);
             if(isdigit(argv[2][0])){
                 largura=atoi(argv[2]);
             }else{
                 valido=true;
             }
         }else{
              valido=true;
              altura=atoi(argv[2]);
         }
    }else if(argc==2){
        if(isdigit(argv[1][0])){
            altura=atoi(argv[1]);
        }else{
             valido=true;
        }
    }

    if(altura>100 || largura>100){
        std::cout<<"O limite das dimensões é 100 para a lagura e 100 para a altura"<<std::endl;
        return 0;
    }

    int tamanho=altura * largura;
    DisjSets conjuntos(tamanho);
    unsigned char Maze[ tamanho];
        for ( int i=0; i < (tamanho); i++ ){
            Maze[ i ] = TopWall | RightWall | BottomWall | LeftWall;
            v.push_back(i); //preenche vetor v com os numeros de todas as celulas
        }
        Maze[0] &= ~LeftWall; //apaga primeira parede
        Maze[tamanho-1] &= ~RightWall; //apaga ultima parede


  //embaralha numeros do vetor v
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(v.begin(), v.end(), g);


  int cont=0;
  unsigned char parede;
  //////////***********valido**************//////////////
 if(valido){
  while(conjuntos.find(0)!=conjuntos.find(tamanho-1)){//enquanto o conjunto da primeira casa for diferente do da última casa
      parede = numeroAleatorio(0, 3);//sorteia um numero entre 0 e 3, pra decidir qual parede quebrar
      switch (parede) {
      case 0: //TopWall
        if(v.at(cont)>largura-1){//se tiver na primeira linha, nao quebra a parede de cima
             if ( Maze[ v.at(cont)] & TopWall){//A parede está intacta?
                 if(conjuntos.find(v.at(cont))!=conjuntos.find(v.at(cont)-largura)){
                   Maze[ v.at(cont) ] &= ~TopWall;//quebra a parede
                   Maze[ v.at(cont)-largura ] &= ~BottomWall;
                   conjuntos.unionSets(conjuntos.find(v.at(cont)),conjuntos.find(v.at(cont)-largura));
                 }
             }
        }
          break;
      case 1: //RightWall
          if((v.at(cont)+1)%largura!=0){//se tiver na ultima coluna, nao quebra a parede de cima
               if ( Maze[ v.at(cont)] & RightWall){//A parede está intacta?
                 if(conjuntos.find(v.at(cont))!=conjuntos.find(v.at(cont)+1)){
                   Maze[ v.at(cont) ] &= ~RightWall;//quebra a parede
                   Maze[ v.at(cont)+1 ] &= ~LeftWall;
                   conjuntos.unionSets(conjuntos.find(v.at(cont)),conjuntos.find(v.at(cont)+1));
                 }
               }
          }
          break;
      case 2:
          if((v.at(cont))<tamanho-largura-1){//se tiver na ultima linha, nao quebra a parede de cima
               if ( Maze[ v.at(cont)] & BottomWall){//A parede está intacta?
                   if(conjuntos.find(v.at(cont))!=conjuntos.find(v.at(cont)+largura)){
                     Maze[ v.at(cont) ] &= ~BottomWall;//quebra a parede
                     Maze[ v.at(cont)+largura] &= ~TopWall;
                     conjuntos.unionSets(conjuntos.find(v.at(cont)),conjuntos.find(v.at(cont)+largura));
                   }
               }
          }
          break;
      case 3:
          if((v.at(cont))%largura!=0){//se tiver na primeira coluna, nao quebra a parede de cima
               if ( Maze[ v.at(cont)] & LeftWall){//A parede está intacta?
                   if(conjuntos.find(v.at(cont))!=conjuntos.find(v.at(cont)-1)){
                      Maze[ v.at(cont) ] &= ~LeftWall;//quebra a parede
                      Maze[ v.at(cont)-1 ] &= ~RightWall;
                      conjuntos.unionSets(conjuntos.find(v.at(cont)),conjuntos.find(v.at(cont)-1));
                   }
               }
          }
          break;
      default:
          break;
      }


      //Desenha
      drawMaze(altura,largura,Maze,TopWall,RightWall,BottomWall,LeftWall);
      std::cout<<"Qtd de conjuntos: "<<conjuntos.size()<<std::endl;
      usleep(100000);
      cont++;
      if(cont==(tamanho-1)){
          cont=0;
      }

  }
}else{
  //////////*********totalmente conexo******/////////////
  cont=0;
  //unsigned char parede;
    while (conjuntos.size()!=1) { //enquanto não houver apenas um conjunto
      parede = numeroAleatorio(0, 3);//sorteia um numero entre 0 e 3, pra decidir qual parede quebrar
      switch (parede) {
      case 0: //TopWall
        if(v.at(cont)>largura-1){//se tiver na primeira linha, nao quebra a parede de cima
             if ( Maze[ v.at(cont)] & TopWall){//A parede está intacta?
                 if(conjuntos.find(v.at(cont))!=conjuntos.find(v.at(cont)-largura)){
                   Maze[ v.at(cont) ] &= ~TopWall;//quebra a parede
                   Maze[ v.at(cont)-largura ] &= ~BottomWall;
                   conjuntos.unionSets(conjuntos.find(v.at(cont)),conjuntos.find(v.at(cont)-largura));
                 }
             }
        }
          break;
      case 1: //RightWall
          if((v.at(cont)+1)%largura!=0){//se tiver na ultima coluna, nao quebra a parede de cima
               if ( Maze[ v.at(cont)] & RightWall){//A parede está intacta?
                 if(conjuntos.find(v.at(cont))!=conjuntos.find(v.at(cont)+1)){
                   Maze[ v.at(cont) ] &= ~RightWall;//quebra a parede
                   Maze[ v.at(cont)+1 ] &= ~LeftWall;
                   conjuntos.unionSets(conjuntos.find(v.at(cont)),conjuntos.find(v.at(cont)+1));
                 }
               }
          }
          break;
      case 2:
          if((v.at(cont))<tamanho-largura-1){//se tiver na ultima linha, nao quebra a parede de cima
               if ( Maze[ v.at(cont)] & BottomWall){//A parede está intacta?
                   if(conjuntos.find(v.at(cont))!=conjuntos.find(v.at(cont)+largura)){
                     Maze[ v.at(cont) ] &= ~BottomWall;//quebra a parede
                     Maze[ v.at(cont)+largura] &= ~TopWall;
                     conjuntos.unionSets(conjuntos.find(v.at(cont)),conjuntos.find(v.at(cont)+largura));
                   }
               }
          }
          break;
      case 3:
          if((v.at(cont))%largura!=0){//se tiver na primeira coluna, nao quebra a parede de cima
               if ( Maze[ v.at(cont)] & LeftWall){//A parede está intacta?
                   if(conjuntos.find(v.at(cont))!=conjuntos.find(v.at(cont)-1)){
                      Maze[ v.at(cont) ] &= ~LeftWall;//quebra a parede
                      Maze[ v.at(cont)-1 ] &= ~RightWall;
                      conjuntos.unionSets(conjuntos.find(v.at(cont)),conjuntos.find(v.at(cont)-1));
                   }
               }
          }
          break;
      default:
          break;
      }


      //Desenha
      drawMaze(altura,largura,Maze,TopWall,RightWall,BottomWall,LeftWall);
      std::cout<<"Qtd de conjuntos: "<<conjuntos.size()<<std::endl;
      usleep(100000);
      cont++;
      if(cont==(tamanho-1)){
          cont=0;
      }

  }

}

    std::cout<<"Digite f para encontrar a saída "<<std::endl;
    char comando;
    std::cin>>comando;

   if(comando=='f'){

   //backtracking
     std::stack <int> path;//pilha que armazena o caminho sendo percorrido

     int c=0; //armazena a posicao que esta sendo percorrida na matriz Maze
     path.push(c); //adiciona a posicao 0 na pilha
     Maze[c] |= trackedPath;
     while(path.top()!=tamanho-1){

         if(!(Maze[c] & RightWall) && !(Maze[c+1] & trackedPath)){//se não tiver parede a direita e a direita ainda nao tiver sido percorrida
             c++; //posicao anda uma coluna
             path.push(c);
             Maze[c] |= trackedPath; //marca essa posicao como percorrida
         }else if(!(Maze[c] & BottomWall) && !(Maze[c+largura] & trackedPath)){//se nao tiver a parede de baixo e a celular de baixo ainda nao tiver sido percorrida
             c=c+largura;//posicao desce uma linha
             path.push(c);
             Maze[c] |= trackedPath;
         }else if(!(Maze[c] & LeftWall) && !(Maze[c-1] & trackedPath)){//se nao tiver a parede a esquerda e a esquerda nao tiver sido percorrida
             c=c-1; //posicao volta uma coluna
             path.push(c);
             Maze[c] |= trackedPath;
         }else if(!(Maze[c] & TopWall) && !(Maze[c-largura] & trackedPath)){//se nao tiver a parede de cima e a celula de cima nao tiver sido percorrida
              c=c-largura;
              path.push(c);
              Maze[c] |= trackedPath;
         }else if(!(Maze[c] & RightWall) && (Maze[c+1] & trackedPath) && !(Maze[c+1] & wrongTrackedPath)){
             Maze[c] |= wrongTrackedPath;
             path.pop();
             c=c+1;
        }else if(!(Maze[c] & BottomWall) && (Maze[c+largura] & trackedPath) && !(Maze[c+largura] & wrongTrackedPath)){
              Maze[c] |= wrongTrackedPath;
              path.pop();
              c=c+largura;
         }else if(!(Maze[c] & LeftWall) && (Maze[c-1] & trackedPath) && !(Maze[c-1] & wrongTrackedPath)){
             Maze[c] |= wrongTrackedPath;
             path.pop();
             c=c-1;
        }else if(!(Maze[c] & TopWall) && (Maze[c-largura] & trackedPath) && !(Maze[c-largura] & wrongTrackedPath)){
             Maze[c] |= wrongTrackedPath;
             path.pop();
             c=c-largura;
        }

         //Desenha Primeira opcao
       /*  for(int i=0; i<altura; i++){
             for(int j=largura*i; j<largura*i+largura; j++){
                 if(Maze[j] & TopWall){//se tem a parede de cima
                    std::cout<< "####";//desenha a parede de cima
                 }else{
                     if(Maze[j] & wrongTrackedPath){
                         std::cout<< "#**#";
                     }else if(Maze[j] & trackedPath){
                         std::cout<< "#@@#";
                     }else{ std::cout<< "#  #";}
                 } //senao desenha apenas as diagonais
             }
             std::cout<<std::endl;
             for(int j=largura*i; j<largura*i+largura; j++){
                 if(Maze[j] & LeftWall){
                     if(Maze[j] & wrongTrackedPath){
                         std::cout<< "#*";
                     }else if(Maze[j] & trackedPath){
                         std::cout<< "#@";
                     }else{ std::cout<< "# ";}
                 }else{
                     if(Maze[j] & wrongTrackedPath){
                         std::cout<< "**";
                     }else if(Maze[j] & trackedPath){
                         std::cout<< "@@";
                     }
                     else{std::cout<< "  ";}

                 }
                 if(Maze[j] & RightWall){
                     if(Maze[j] & wrongTrackedPath){
                         std::cout<< "*#";
                     }else if(Maze[j] & trackedPath){
                         std::cout<< "@#";
                     }else{std::cout<< " #";}

                 }else{
                     if(Maze[j] & wrongTrackedPath){
                         std::cout<< "**";
                     }else if(Maze[j] & trackedPath){
                         std::cout<< "@@";
                     }else{std::cout<< "  ";}
                      }
             }
             std::cout<<std::endl;
             for(int j=largura*i; j<largura*i+largura; j++){
                 if(Maze[j] & BottomWall){
                    std::cout<< "####";
                 }else{
                     if(Maze[j] & wrongTrackedPath){
                         std::cout<< "#**#";
                     }else if(Maze[j] & trackedPath){
                         std::cout<< "#@@#";
                     }else{ std::cout<< "#  #";}
                 }

             }
             std::cout<<std::endl;
         }*/
         //std::cout<<std::endl;
         // std::cout<<c<<std::endl;







         /*system("clear");
         for(int i=0; i<altura; i++){
               for(int j=largura*i; j<largura*i+largura; j++){//percorre a parede de cima
                   if(Maze[j] & TopWall){//se tem a parede de cima
                      std::cout<< "####";//desenha a parede de cima
                   }else{
                       if(Maze[j-largura] & wrongTrackedPath && Maze[j] & wrongTrackedPath){
                           std::cout<< "#**#";
                       }else if(Maze[j-largura] & trackedPath && Maze[j] & trackedPath){
                           std::cout<< "#@@#";
                       }else{ std::cout<< "#  #";}
                   } //senao desenha apenas as diagonais
               }
               std::cout<<std::endl;
               for(int j=largura*i; j<largura*i+largura; j++){//percorre as paredes laterais
                   if(Maze[j] & LeftWall){
                       if(Maze[j] & wrongTrackedPath){
                           std::cout<< "#*";
                       }else if(Maze[j] & trackedPath){
                           std::cout<< "#@";
                       }else{ std::cout<< "# ";}
                   }else{
                       if(Maze[j] & wrongTrackedPath && Maze[j-1] & wrongTrackedPath){
                           std::cout<< "**";
                       }else if(Maze[j] & wrongTrackedPath && !(Maze[j-1] & trackedPath)){
                           std::cout<< " *";
                       }
                       else if(Maze[j] & trackedPath && Maze[j-1] & trackedPath){
                           std::cout<< "@@";
                       }else if(Maze[j] & trackedPath && !(Maze[j-1] & trackedPath)){
                           std::cout<< " @";
                       }
                       else{std::cout<< "  ";}

                   }
                   if(Maze[j] & RightWall){
                       if(Maze[j] & wrongTrackedPath){
                           std::cout<< "*#";
                       }else if(Maze[j] & trackedPath){
                           std::cout<< "@#";
                       }else{std::cout<< " #";}

                   }else{
                       if(Maze[j] & wrongTrackedPath && Maze[j+1] & wrongTrackedPath){
                           std::cout<< "**";
                       }else if(Maze[j] & wrongTrackedPath && !(Maze[j+1] & trackedPath)){
                           std::cout<< "* ";
                       }
                       else if(Maze[j] & trackedPath && Maze[j+1] & trackedPath){
                           std::cout<< "@@";
                       }else if(Maze[j] & trackedPath && !(Maze[j+1] & trackedPath)){
                           std::cout<< "@ ";
                       }
                       else{std::cout<< "  ";}

                        }
               }
               std::cout<<std::endl;
               for(int j=largura*i; j<largura*i+largura; j++){
                   if(Maze[j] & BottomWall){
                      std::cout<< "####";
                   }else{
                       if(Maze[j+largura] & wrongTrackedPath && Maze[j] & wrongTrackedPath){
                           std::cout<< "#**#";
                       }else if(Maze[j+largura] & trackedPath && Maze[j] & trackedPath){
                           std::cout<< "#@@#";
                       }else{ std::cout<< "#  #";}
                   }

               }
               std::cout<<std::endl;
           }
           std::cout<<std::endl;*/

         system("clear");
         //Desenha segunda opcao
         for(int i=0; i<altura; i++){
             for(int j=largura*i; j<largura*i+largura; j++){
                 if(Maze[j] & TopWall){//se tem a parede de cima
                    std::cout<< "####";//desenha a parede de cima
                 }else{std::cout<< "#  #";} //senao desenha apenas as diagonais
             }
             std::cout<<std::endl;
             for(int j=largura*i; j<largura*i+largura; j++){
                 if(Maze[j] & LeftWall){
                     if(Maze[j] & wrongTrackedPath){
                         std::cout<< "#*";
                     }else if(Maze[j] & trackedPath){
                         std::cout<< "#@";
                     }else{ std::cout<< "# ";}
                 }else{
                     if(Maze[j] & wrongTrackedPath){
                         std::cout<< " *";
                     }else if(Maze[j] & trackedPath){
                         std::cout<< " @";
                     }
                     else{std::cout<< "  ";}

                 }
                 if(Maze[j] & RightWall){
                     if(Maze[j] & wrongTrackedPath){
                         std::cout<< "*#";
                     }else if(Maze[j] & trackedPath){
                         std::cout<< "@#";
                     }else{std::cout<< " #";}

                 }else{
                     if(Maze[j] & wrongTrackedPath){
                         std::cout<< "* ";
                     }else if(Maze[j] & trackedPath){
                         std::cout<< "@ ";
                     }else{std::cout<< "  ";}
                      }
             }
             std::cout<<std::endl;
             for(int j=largura*i; j<largura*i+largura; j++){
                 if(Maze[j] & BottomWall){
                    std::cout<< "####";
                 }else{std::cout<< "#  #";}
             }
             std::cout<<std::endl;
         }
         std::cout<<std::endl;
            usleep(500000);


     }
   }


    return 0;
}
