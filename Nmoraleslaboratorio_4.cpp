#include <fstream>
#include <iostream>
#include <string>

using namespace std;

struct Node {
    int info;
    Node* left;
    Node* right;
};

// Crear un nuevo nodo
Node* createNode(const int& data) {
    Node* newNode = new Node;
    newNode->info = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

class Arbol {
private:
    Node* root;

    // Recorrer el arbol en preorden y escribir en el archivo
    // aqui tuve un problema cuando mostraban los grafos y era que las flechas se volvian a los
    // mismos nodos y me aparecian unos warnings y el problema era de unos caracteres que no estaban permitidos como nombres en graphviz

    void recorrer(Node* node, ofstream& fp) {
        if (node != nullptr) {
            if (node->left != nullptr) {
                fp << node->info << "->" << node->left->info << ";" << endl;
            } else {
                string cadena = "\"" + to_string(node->info) + "i\"";
                fp << cadena << "[shape=point];" << endl;
                fp << node->info << "->" << cadena << ";" << endl;
            }

            if (node->right != nullptr) {
                fp << node->info << "->" << node->right->info << ";" << endl;
            } else {
                string cadena = "\"" + to_string(node->info) + "d\"";
                fp << cadena << "[shape=point];" << endl;
                fp << node->info << "->" << cadena << ";" << endl;
            }

            recorrer(node->left, fp);
            recorrer(node->right, fp);
        }
    }

    // Insertar nodo
    Node* insertNode(Node*& root, const int& info) {
        if (root == nullptr) {
            root = createNode(info);
        } else if (info < root->info) {
            root->left = insertNode(root->left, info);
        } else if (info > root->info) {
            root->right = insertNode(root->right, info);
        } else {
            cout << "El dato ya existe en el arbol" << endl;
        }
        return root;
    }

    // Eliminar nodo
    Node* deleteNode(Node*& root, const int& search) {
        if (root == nullptr) {
            return root;
        }
        if (search < root->info) {
            root->left = deleteNode(root->left, search);
        } else if (search > root->info) {
            root->right = deleteNode(root->right, search);
        } else {
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }
            Node* temp = root->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            root->info = temp->info;
            root->right = deleteNode(root->right, temp->info);
        }
        return root;
    }

    // Modificar un nodo del arbol
    bool modifyNode(Node*& root, const int& info) {
        if (root == nullptr) {
            return false;
        } else if (root->info == info) {
            cout << "Ingrese nueva informacion para el nodo: ";
            int newNode;
            while (!(cin >> newNode)) {
                cout << "Entrada no valida. Por favor ingrese un numero: ";
                cin.clear();
                cin.ignore(123, '\n');
            }
            root->info = newNode;
            return true;
        } else if (info < root->info) {
            return modifyNode(root->left, info);
        } else {
            return modifyNode(root->right, info);
        }
    }

    // contenido del arbol en preorden
    void preOrderPrint(Node* root) {
        if (root == nullptr) {
            return;
        }
        cout << root->info << " ";
        preOrderPrint(root->left);
        preOrderPrint(root->right);
    }

    // contenido del arbol en inorden
    void inOrderPrint(Node* root) {
        if (root == nullptr) {
            return;
        }
        inOrderPrint(root->left);
        cout << root->info << " ";
        inOrderPrint(root->right);
    }

    // contenido del arbol en posorden
    void postOrderPrint(Node* root) {
        if (root == nullptr) {
            return;
        }
        postOrderPrint(root->left);
        postOrderPrint(root->right);
        cout << root->info << " ";
    }

public:
    Arbol() {
        root = nullptr;
    }

    // Insertar un nuevo nodo en el arbol
    void insert(const int& info) {
        root = insertNode(root, info);
    }

    // Eliminar un nodo del arbol
    void remove(const int& search) {
        root = deleteNode(root, search);
    }

    // Modificar un nodo del arbol
    bool modify(const int& info) {
        return modifyNode(root, info);
    }

    // Mostrar el contenido del arbol en preorden
    void printPreOrder() {
        preOrderPrint(root);
        cout << endl;
    }

    // Mostrar el contenido del arbol en inorden
    void printInOrder() {
        inOrderPrint(root);
        cout << endl;
    }

    // Mostrar el contenido del arbol en posorden
    void printPostOrder() {
        postOrderPrint(root);
        cout << endl;
    }

    // Generar el grafo correspondiente
    void generateGraph() {
        ofstream fp("grafo.txt");
        fp << "digraph G {" << endl;
        fp << "node [style=filled fillcolor=yellow];" << endl;
        recorrer(root, fp);
        fp << "}" << endl;
        fp.close();
        system("dot -Tpng -o grafo.png grafo.txt");
        system("eog grafo.png");
    }
};

int main() {
    Arbol arbol;

    // los valores iniciales
    arbol.insert(120);
    arbol.insert(87);
    arbol.insert(140);
    arbol.insert(43);
    arbol.insert(99);
    arbol.insert(130);
    arbol.insert(22);
    arbol.insert(65);
    arbol.insert(93);
    arbol.insert(135);
    arbol.insert(56);

    int option;
    do {
        cout << "1. Insertar numero" << endl;
        cout << "2. Eliminar numero" << endl;
        cout << "3. Modificar numero" << endl;
        cout << "4. Mostrar contenido del arbol" << endl;
        cout << "5. Generar grafo" << endl;
        cout << "6. Salir" << endl;
        cout << "Ingrese una opcion: ";
        while (!(cin >> option) || option < 1 || option > 6) {
            cout << "Opcion no valida. Por favor ingrese un numero entre 1 y 6: ";
            cin.clear();
            cin.ignore(123, '\n');
        }

        switch (option) {
            case 1: {
                int info;
                cout << "Ingrese un numero: ";
                while (!(cin >> info)) {
                    cout << "Entrada no valida. Por favor ingrese un numero: ";
                    cin.clear();
                    cin.ignore(123, '\n');
                }
                arbol.insert(info);
                break;
            }
            case 2: {
                int search;
                cout << "Ingrese un numero para eliminar: ";
                while (!(cin >> search)) {
                    cout << "Entrada no valida. Por favor ingrese un numero: ";
                    cin.clear();
                    cin.ignore(123, '\n');
                }
                arbol.remove(search);
                break;
            }
            case 3: {
                int info;
                cout << "Ingrese un numero para modificar: ";
                while (!(cin >> info)) {
                    cout << "Entrada no valida. Por favor ingrese un numero: ";
                    cin.clear();
                    cin.ignore(123, '\n');
                }
                arbol.modify(info);
                break;
            }
            case 4: {
                cout << "Preorden: ";
                arbol.printPreOrder();
                cout << "Inorden: ";
                arbol.printInOrder();
                cout << "Posorden: ";
                arbol.printPostOrder();
                break;
            }
            case 5: {
                arbol.generateGraph();
                break;
            }
            default:
                break;
        }
    } while (option != 6);


    return 0;
}
