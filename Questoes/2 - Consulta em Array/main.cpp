#include <map>
#include <iterator>

 /******************************************************************************

#2 Dado um array de inteiro, o programa deve receber um int e retornar quantas vezes ele existe no array


*******************************************************************************/
typedef std::map<int, int> mapa; // std::map<Key, T>;

mapa criarMapa(int* lst, int tam);
void printMapa(mapa mp);

int main(int argc, char** argv) {
	
	int lista[] = {2, 4, 6, 4, 6, 7, 9, 6, 1, 3, 3, 5, 7, 8, 4, 2, 2, 4, 5, 6, 8, 9, 6, 4, 4, 6, 7, 1, 3, 4, 2, 3, 3, 4, 2, 5};
	int tamArray = (int)(sizeof(lista) / sizeof(lista[0]));
	
	mapa mp = criarMapa(lista, tamArray);
	
	printMapa(mp);
		
	system("pause");
	return 0;
}

mapa criarMapa(int* lst, int tam) {
	mapa mp;
	printf("Tamanho lista: %d\n", tam);
	int i;
	
//	mp.insert(std::make_pair(1, 11));
//	mp.insert(std::make_pair(2, 22));
//	mp.insert(std::make_pair(3, 33));
	
	for(i = 0; i < tam; i++) {
		int el = lst[i];
		mp[el]++;
	}
	
	return mp;
}

void printMapa(mapa mp) {
	printf("Tamanho mapa: %d\n", mp.size());
	
	printf("Mapa:\n");
	mapa::iterator it = mp.begin();
	while(it != mp.end()) {
		printf("<%d, %d>\n\n", it->first, it->second);
		++it;
	}
	printf("<%d, %d>\n\n", 10, mp[10]);
}
