/**
 * Disjoint set class.
 * Use union by rank and path compression.
 * Elements in the set are numbered starting at 0.
 */

#include <vector>
#include <iostream>

class DisjSets
{
  public:
    // Generates the disjoint sets, one for each element.
    explicit DisjSets( int numElements ){
        for(int i=0; i<numElements; i++){
            s.push_back(i);
    }
    }

    // Return set's name containing x
    int find( int x ) const{
        while (s.at(x)!=x){ //enquanto x for diferente do indice do vetor
            x=s.at(x); //atualiza o valor de x até ele ter o mesmo valor do indice (o valor do pai do conjunto tem o mesmo valor do indice)
        }
        return s.at(x);
}
    // Return set's name containing x, with path compression.
    int find( int x ){
        int aux;
        aux=x;
        while (s.at(aux)!=aux){
            aux=s.at(aux); //aux vai armazenar o pai do conjunto
        }
        int aux2;
        while (s.at(x)!=x){
            aux2=x;
            x=s.at(x);
            s.at(aux2)=aux; //todos vao apontar pro pai do conjunto

        }
        return aux;
    }

    // Merge two sets, by size or by estimated heigh (also knwon as rank).
    void unionSets( int root1, int root2 ){
        //descobrir a altura de cada um
        int altura1,altura2, max;
        altura1=0;
        max=0; //armazena altura maxima
        for(unsigned int i=0; i<s.size(); i++){ //calcula a altura 1
                if(find(i)==root1){
                    int aux=i;
                    while (aux!=root1){
                        aux=s.at(aux);
                        altura1++;
                    }
                    if(altura1>max){
                        max=altura1;
                    }
                    altura1=0;
                }
        }
        altura1=max;
        altura2=0;
        max=0;
        for(unsigned int i=0; i<s.size(); i++){//calcular a altura 2
                if(find(i)==root2){
                    int aux=i;
                    while (aux!=root2){
                        aux=s.at(aux);
                        altura2++;
                    }
                    if(altura2>max){
                        max=altura2;
                    }
                    altura2=0;
                }
        }
        altura2=max;

        //std::cout<<"altura1 "<<altura1<<std::endl;
        //std::cout<<"altura2 "<<altura2<<std::endl;
        if(altura1>altura2){
            s.at(root2)=root1;
        }else{
            s.at(root1)=root2;
        }

    }


    // Return the current number of disjoint sets
    int size( ) const{
        int tamanho=0;
        std::vector<int>v; //vai armazenar o pai de cada conjunto.
        int aux;
        bool flag;//indica se o elemento está ou não em v.
        for(unsigned int i=0; i<s.size(); i++){
            aux=this->find(i);
            flag=false;
             for(unsigned int j=0; j<v.size(); j++){//percorre o vetor que armazena todos os pais
                 if(aux==v.at(j)){ //ja ta no vetor que armazena o pai de cada conjunto
                     flag=true; //como ja está no vetor, ele nao adiciona o valor novamente
                     break;
                 }
             }
             if(flag==false){
                 v.push_back(aux);
                 tamanho++;
             }
        }
      /* for(unsigned int i=0; i<s.size(); i++){
            std::cout<< s.at(i)<<" ";
        }
        std::cout<<std::endl;*/
        return tamanho;
    }

  private:
    std::vector<int> s;
};

//#include "DisjSets.inl"
