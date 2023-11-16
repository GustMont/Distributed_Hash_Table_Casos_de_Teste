// importando bibliotecas
#include <iostream>
using namespace std;

// instanciação da classe Client
class Client {
private:
  int imei_;
  std::string login_;
public:
//construtor padrão
  Client();
//construtor com dois parâmetros
  Client(int imei_, std::string login_);
//getters
  string getLogin() const;
  int getImei() const;
};

// implementação do construtor padrão Client
Client::Client() {
  this->imei_ = -1;
  this->login_ = "";
};
// implementação do contrutor com parametros
Client::Client(int imei_, std::string login_) {
  this->imei_ = imei_;
  this->login_ = login_;
} 
// funções de acesso dos getters
string Client::getLogin() const {
  return login_;
} 
int Client::getImei() const { 
  return imei_; 
}

// instanciação da classe Hash
class Hash {
public:
  // tabela hash
  Hash(int max_items = 100);
  ~Hash();
  bool isFull() const;
  int getLength() const;
  // função para recuperar item da tabela hash
  void retrieveItem(Client &client, bool &found);
  // função para inserir um item da tabela hash
  void insertItem(Client client);
  // função para deletar um item da tabela hash
  void deleteItem(Client client);
  void print();
private:
  int getHash(Client client);
  int max_items;
  int lenght;
  Client *structure;
};

//construtor hash com o valor mínimo 0 e máximo como argumento
Hash::Hash(int max) {
  lenght = 0;
  max_items = max;
  structure = new Client[max_items];
}

// destrutor da classe hash
Hash::~Hash() { delete[] structure; }
// função para verificar se tabela hash está cheia
bool Hash::isFull() const { return (lenght == max_items); }
// retorna o comprimeno da tabela hash
int Hash::getLength() const { return lenght; }

// função para buscar um item na tabela hash
void Hash::retrieveItem(Client &client, bool &f) {
  int location_1 = getHash(client);
  bool find = true;
  int location = location_1;
  do {
    if (structure[location].getImei() == client.getImei() ||
        structure[location].getImei() == -1)
      find = false;
    else
      location = (location + 1) % max_items;
  } while (location != location_1 && find);
  int found = (structure[location].getImei() == client.getImei());
  if (found) {
    client = structure[location];
  }
}
// função para inserir um item na tabela tratando colisões
void Hash::insertItem(Client client) {
  int location = getHash(client);
  while (structure[location].getImei() > 0)
    location = (location + 1) % max_items;
  structure[location] = client;
  lenght++;
}
// função para deletar um item na tabela
void Hash::deleteItem(Client client) {
  int location_1 = getHash(client);
  bool find = true;
  int location = location_1;
  do {
    if (structure[location].getImei() == client.getImei() ||
        structure[location].getImei() == -1)
      find = false;
    else
      location = (location + 1) % max_items;
  } while (location != location_1 && find);

  if (structure[location].getImei() == client.getImei()) {
    structure[location] = Client(-2, "");
    lenght--;
  }
}
// função para mostrar na tela a tabela hash
void Hash::print() {
  for (int i = 0; i < max_items; i++) {
    cout << i << ":" << structure[i].getImei() << ", "
         << structure[i].getLogin() << endl;
  }
}

int Hash::getHash(Client client) { return client.getImei() % max_items; }


int main() {
  
  cout << "Caso de Teste 1 - Criação de Tabela Hash"
       << endl;
  Hash clientHash(6);
  int imei[5] = {0, 1, 2,
                      3, 4};
  string login[5] = {"jonasvianasalesmonteiro@exemplo.com", "paulosilveirasantos@exemplo.com",
                     "carlitos@exemplo.com", "thiagao@exemplo.com",
                     "mari@exemplo.com"};

  for (int i = 0; i < 5; i++) {
    Client client = Client(imei[i], login[i]);
    clientHash.insertItem(client);
  }
  clientHash.print();
  cout << "---------------------------------------------------" << endl;

  cout << "Caso de Teste 2 - Buscar item salvo na Tabela Hash a partir do Imei"
       << endl
       << "Resultado da busca:" << endl
       << endl;
  Client client(2, "");
  bool found = false;
  clientHash.retrieveItem(client, found);
  cout << client.getLogin() << ""

       << endl;
  cout << "---------------------------------------------------" << endl;
  
  cout << "Caso de Teste 3 - Deleção de item da Tabela Hash"
       << endl;
  Client client_delete(1, "");
  clientHash.deleteItem(client_delete);
  clientHash.print();
  cout << "---------------------------------------------------" << endl;

  cout << "Caso de Teste 4 - Adicionar novo item, tratando a colisão adicionando-o no próximo espaço vazio"
       << endl;
  Client client_add(13, "estagiario@exemplo.com");
  clientHash.insertItem(client_add);
  clientHash.print();
  cout << "---------------------------------------------------" << endl;

  cout << "Caso de Teste 5 - Buscar item adicionado que sofreu tratamento de colisão"
       << endl
       << "Resultado da busca:" << endl

       << endl;
  Client client_recov(13, "");
  bool found_recov = false;
  clientHash.retrieveItem(client_recov, found);
  cout << client_recov.getLogin() << ""
       << endl;
  cout << "---------------------------------------------------" << endl;
  }