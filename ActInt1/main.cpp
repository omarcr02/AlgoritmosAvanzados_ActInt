#include <iostream>
#include <fstream>
#include <string>


using namespace std;

//Declaración de funciones
string cargaArchivo(string filename);
int palindromoMasLargo(string str, string archi);
void KMPBuscar(string pat, string txt, string archi);
void calculaLPSArray(string pat, int M, int* lps);
void imprimir_lstring(string X, string Y, string archi);


int main()
{
    string trans1, trans2, mcode1, mcode2, mcode3;
    //Carga de archivos
    string archivo = "transmission1.txt";
    string archivo2 = "transmission2.txt";
    string code1 = "mcode1.txt";
    string code2 = "mcode2.txt";
    string code3 = "mcode3.txt";
    //Lectura de cadenas.
    trans1 = cargaArchivo(archivo);
    trans2 = cargaArchivo(archivo2);
    mcode1 = cargaArchivo(code1);
    mcode2 = cargaArchivo(code2);
    mcode3 = cargaArchivo(code3);

    //Buscar subcadena
    cout << "BUSQUEDA DE SUBCADENAS:" << endl;
    KMPBuscar(mcode1, trans1, archivo);
    KMPBuscar(mcode2, trans1, archivo);
    KMPBuscar(mcode3, trans1, archivo);
    KMPBuscar(mcode1, trans2, archivo2);
    KMPBuscar(mcode2, trans2, archivo2);
    KMPBuscar(mcode3, trans2, archivo2);

    //Palindromo
    cout << "PALINDROMO: " << endl;
    palindromoMasLargo(trans1, archivo);
    palindromoMasLargo(trans2, archivo2);


    //Subcadena comun mas larga
    cout << "SUBCADENA COMUN MAS LARGA" << endl;
    imprimir_lstring(trans1, trans2, archivo);


    return 0;
}

string cargaArchivo(string filename)
{
    char byte = 0;
    ifstream input_file(filename);
    if (!input_file.is_open()) {
        cerr << "No se pudo abrir el archivo '"
             << filename << "'" << endl;
    }
    string cadena;
    while (!input_file.eof()) {
        string s;
        //  cout << s << endl;
        getline(input_file, s);
        cadena = cadena + s;

    }
    input_file.close();
    // cout << cadena << endl;



    return cadena;
}


int palindromoMasLargo(string str, string archi)

{
    int n = str.size(); // calculando tamaño del string
    if (n < 2)
        return n; // si la cadena está vacía, el tamaño será 0. si n==1 entonces, la respuesta será 1(solo, el carácter siempre será palíndromo)

    int maxLength = 1, inicio = 0;
    int bajo, altura;
    for (int i = 0; i < n; i++) {
        bajo = i - 1;
        altura = i + 1;
        while (altura < n
               && str[altura] == str[i]) // incrementa altura
            altura++;

        while (bajo >= 0
               && str[bajo] == str[i]) // decrementa 'bajo'
            bajo--;

        while (bajo >= 0 && altura < n
               && str[bajo] == str[altura]) {
            bajo--;
            altura++;
        }

        int length = altura - bajo - 1;
        if (maxLength < length) {
            maxLength = length;
            inicio = bajo + 1;
        }
    }


    cout << inicio + 1 <<" " << (inicio+maxLength) << " del archivo  " << archi <<endl;
    //cout << str.substr(inicio, maxLength) << endl;

    return maxLength;
}

void KMPBuscar(string pat, string txt, string archi)
{
    int M = pat.length();
    int N = txt.length();

    // Crea una cadena de caracteres el cual sera el sufijo mas largo
    int lps[M]; // longitud del patron del string

    // Preprocesa el patron
    calculaLPSArray(pat, M, lps);

    int i = 0; // index para txt
    int j = 0; // index para pat
    while ((N - i) >= (M - j)) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }

        if (j == M) {
            cout << "TRUE " << i - j + 1 << " del archivo: " << archi << endl;
            j = lps[j - 1];
            return;
        }


        else if (i < N && pat[j] != txt[i]) {
            //Si no concuerda el caracter haz el match de todas formas
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
    cout << "FALSE" << " del archivo: " << archi << endl;

}

// Rellena lps[] para patrón dado pat[0..M-1]
void calculaLPSArray(string pat, int M, int* lps)
{
    // longitud del sufijo de prefijo más largo anterior
    int len = 0;

    lps[0] = 0; // lps es siempre cero

    // El ciclo calcila  lps[i] para i = 1 to M-1
    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else // (pat[i] != pat[len])
        {

            if (len != 0) {
                len = lps[len - 1];


            }
            else // if (len == 0)
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void imprimir_lstring(string X, string Y, string archi){
    int m = X.length();
    int n = Y.length();
    int longest[m + 1][n + 1];
    int len = 0;
    int row, col;
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                longest[i][j] = 0;
            else if (X[i - 1] == Y[j - 1]) {
                longest[i][j] = longest[i - 1][j - 1] + 1;
                if (len < longest[i][j]) {
                    len = longest[i][j];
                    row = i;
                    col = j;
                }
            }
            else
                longest[i][j] = 0;
        }
    }
    if (len == 0) {
        cout << "No hay existencia de subcadena comun entre los archivos";
        return;
    }

    char* final_str = (char*)malloc((len + 1) * sizeof(char));
    final_str[len] = '\0';
    cout << row - len + 1 << " "  << row << " En el archivo: " << archi << endl;
    while (longest[row][col] != 0) {
        final_str[--len] = X[row - 1];
        row--;
        col--;
    }
    //cout << final_str;


}