import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) throws IOException {

        System.out.println("================================================================");
        System.out.println("IESB 20201 - Análise de Algoritmos - Professor Felippe Rodrigues");
        System.out.println("Programa Compressor Huffman.  Aluno: Gabriel Ibañez - 1812130004");
        System.out.println("================================================================\n");

        // carregando o arquivo texto
        File file = new File("C:\\Users\\ibane\\Desktop\\1GABRIEL\\2020\\IESB 2020\\DISCIPLINAS 20201\\Análise de Algoritmos\\Huffman\\S2.txt");
        BufferedReader bufferedReader = new BufferedReader(new FileReader(file));

        String line = null;

        List<String> textoOriginal = new ArrayList<String>();
        List<Nodo> listaDeNodos = new ArrayList<>();
        List<Nodo> novaListaDeNodos = new ArrayList<>();
        List<Character> listaDeCaracteres = new ArrayList<>();
        List<Integer> frequenciaDosCaracteres = new ArrayList<>();
        List<String> listaDeCodigos = new ArrayList<String>();

        int frequenciaTotal = 0;

        char carac;

        while ( (carac = (char) bufferedReader.read()) != 65535) {
            if (carac == '\r') carac = '¬';
            if (carac == '\n') carac = '¨';
            if(!listaDeCaracteres.contains(carac)) {

                listaDeCaracteres.add(carac);
                Nodo nodo1 = new Nodo (""+carac,"","",1,-1);
                listaDeNodos.add(nodo1);
                frequenciaTotal++;
            } else {

                listaDeNodos.get(listaDeCaracteres.indexOf(carac)).f++;
                frequenciaTotal++;
            }
            textoOriginal.add(""+carac);
        }

        System.out.println("Dados do arquivo:");
        System.out.println("\tTotal de carateres no arquivo: " + frequenciaTotal);
        System.out.println("\tTotal de caracteres distintos: "+listaDeCaracteres.size());
        System.out.println("\tObs.: a quebra de linha foi representada pelos caracteres ¬ e ¨");

        int qtdbits = 0;
        while (Math.pow(2,qtdbits) < listaDeCaracteres.size() ){
            qtdbits++;
        }

        System.out.print("\n\tLista de ocorrências de cada caracter: (Digite qualquer tecla e ENTER) ");

        Scanner s=new Scanner(System.in);
        String l = s.next();
        double p = 0.0;

        for (int i = 0; i < listaDeNodos.size(); i++){
            frequenciaDosCaracteres.add(listaDeNodos.get(i).f);
            p=listaDeNodos.get(i).f*100;
            System.out.printf("\t\tCaracter "+listaDeNodos.get(i).caracter+ "\tFrequência: "+frequenciaDosCaracteres.get(i)+" \t(%.2fl%%)\n",p/frequenciaTotal);
        }

        int pos1 = 0, pos2 = 0, aux = 0; boolean repetido = false;
        Nodo s0 = new Nodo("","","",0,-1);
        Nodo s1 = new Nodo("","","",0,-1);


        while (aux < frequenciaTotal ){
            // procura a posição do caracter com menor frequência:
            pos1 = 0;
            aux = frequenciaTotal;
            for (int i = 0; i < listaDeNodos.size(); i++) {
                if (listaDeNodos.get(i).f < aux) {
                    aux = listaDeNodos.get(i).f;
                    pos1 = i;
                }
            }
            s0.caracter = listaDeNodos.get(pos1).caracter;
            s0.f = listaDeNodos.get(pos1).f;
            listaDeNodos.remove(pos1);

            pos2 = 0;
            aux = frequenciaTotal;
            for (int i = 0; i < listaDeNodos.size(); i++) {
                if (listaDeNodos.get(i).f < aux) {
                    aux = listaDeNodos.get(i).f;
                    pos2 = i;
                }
            }
            s1.caracter = listaDeNodos.get(pos2).caracter;
            s1.f = listaDeNodos.get(pos2).f;
            listaDeNodos.remove(pos2);

            Nodo X = new Nodo(s0.caracter+"+"+s1.caracter,s0.caracter,s1.caracter,s0.f+s1.f,-1);
            aux = X.getF();

            listaDeNodos.add(X);
            novaListaDeNodos.add(X);
        }

        System.out.print("\nÁrvore de Huffman em ordem crescente de frequência sem as folhas: (Digite qualquer tecla + ENTER) ");
        l = s.next();
        System.out.println("");

        for (int i = 0; i < novaListaDeNodos.size(); i++){
            System.out.println("Nodo "+i+": " + novaListaDeNodos.get(i).caracter+ " Frequência: "+novaListaDeNodos.get(i).f);
            novaListaDeNodos.get(i).setP(i);
        }

        System.out.print("\nTabela dos códigos de Huffman para cada caractere: (Digite qualquer tecla + ENTER) ");
        l = s.next();
        System.out.println("");
        String caracter = "";
        String codigo = "";
        for (int w = 0; w < listaDeCaracteres.size(); w++){
            caracter = listaDeCaracteres.get(w).toString();
            codigo = "";
            int nodoAtual = novaListaDeNodos.get(novaListaDeNodos.size()-1).p;
            int contador = 1; boolean continua = true;
            String strAux = "", filho0 = "", filho1="";
            while (contador < novaListaDeNodos.size() && continua ){

                filho0 = novaListaDeNodos.get(nodoAtual).filho0;
                filho1 = novaListaDeNodos.get(nodoAtual).filho1;

                if (filho0.contains(caracter)) {
                    codigo = codigo + "0";
                    strAux = novaListaDeNodos.get(nodoAtual).filho0;
                    for (int i = 0; i < novaListaDeNodos.size(); i++){
                        if (novaListaDeNodos.get(i).caracter.contains(strAux)){
                            nodoAtual = novaListaDeNodos.get(i).p;
                            break;
                        }
                    }
                }

                if (filho1.contains(caracter)) {
                    codigo = codigo + "1";
                    strAux = novaListaDeNodos.get(nodoAtual).filho1;
                    for (int i = 0; i < novaListaDeNodos.size(); i++){
                        if (novaListaDeNodos.get(i).caracter.contains(strAux)){
                            nodoAtual = novaListaDeNodos.get(i).p;
                            break;
                        }
                    }
                }

                if (novaListaDeNodos.get(nodoAtual).filho0.contains(caracter) && (novaListaDeNodos.get(nodoAtual).filho0.length()==1)){
                    codigo = codigo + "0";
                    continua = false;
                }

                if (novaListaDeNodos.get(nodoAtual).filho1.contains(caracter) && (novaListaDeNodos.get(nodoAtual).filho1.length()==1)){
                    codigo = codigo + "1";
                    continua = false;
                }
                contador++;
            }

            listaDeCodigos.add(codigo);
            p=frequenciaDosCaracteres.get(w)*100;
            System.out.printf("\t\tCaracter "+ listaDeCaracteres.get(w) + "\tFrequência: "+frequenciaDosCaracteres.get(w)+" \t(%.2fl%%)\t Código: "+ listaDeCodigos.get(w)+"\n",p/frequenciaTotal);
        }





        for (int i = 0; i < listaDeNodos.size(); i++){
            frequenciaDosCaracteres.add(listaDeNodos.get(i).f);
        }

        System.out.println("\nDiferentemente do método de tamanho fixo, o método de Hufmman codifica");
        System.out.println("os caracteres com maior frequencia em códigos de menor tamanho (menos bits)");

        System.out.print("\nTabela com o tamanho ocupado por cada caractere no arquivo todo: (Digite qualquer tecla + ENTER)");
        l = s.next();
        System.out.println("");

        int tamanhoFinal = 0;

        for (int w = 0; w < listaDeCaracteres.size(); w++){
            caracter = listaDeCaracteres.get(w).toString();
            codigo = "";
            int nodoAtual = novaListaDeNodos.get(novaListaDeNodos.size()-1).p;

            int contador = 1; boolean continua = true;
            String strAux = "", filho0 = "", filho1="";
            while (contador < novaListaDeNodos.size() && continua ){

                filho0 = novaListaDeNodos.get(nodoAtual).filho0;
                filho1 = novaListaDeNodos.get(nodoAtual).filho1;

                if (filho0.contains(caracter)) {
                    codigo = codigo + "0";
                    strAux = novaListaDeNodos.get(nodoAtual).filho0;
                    for (int i = 0; i < novaListaDeNodos.size(); i++){
                        if (novaListaDeNodos.get(i).caracter.contains(strAux)){
                            nodoAtual = novaListaDeNodos.get(i).p;
                            break;
                        }
                    }
                }
                if (filho1.contains(caracter)) {
                    codigo = codigo + "1";
                    strAux = novaListaDeNodos.get(nodoAtual).filho1;
                    for (int i = 0; i < novaListaDeNodos.size(); i++){
                        if (novaListaDeNodos.get(i).caracter.contains(strAux)){
                            nodoAtual = novaListaDeNodos.get(i).p;
                            break;
                        }
                    }
                }
                if (novaListaDeNodos.get(nodoAtual).filho0.contains(caracter) && (novaListaDeNodos.get(nodoAtual).filho0.length()==1)){
                    codigo = codigo + "0";
                    continua = false;
                }
                if (novaListaDeNodos.get(nodoAtual).filho1.contains(caracter) && (novaListaDeNodos.get(nodoAtual).filho1.length()==1)){
                    codigo = codigo + "1";
                    continua = false;
                }
                contador++;
            }
            listaDeCodigos.add(codigo);
            tamanhoFinal = tamanhoFinal + frequenciaDosCaracteres.get(w)*listaDeCodigos.get(w).length();
            System.out.printf("\t\tCaracter "+ listaDeCaracteres.get(w) + "\tTamanho do código: "+ listaDeCodigos.get(w).length()+" bits\tFrequência: "+ frequenciaDosCaracteres.get(w)+" \t tamanho total no arquivo: "+ frequenciaDosCaracteres.get(w)*listaDeCodigos.get(w).length()+"\n");
        }

        System.out.println("\n\t\tTamanho da cadeia de caracteres necessária para armazenar o arquivo: "+ tamanhoFinal);

        System.err.print("\n\t------ CONCLUSÃO DO EXERCÍCIO ------\n");
        System.out.println("\tConsiderando o método normal de armazenamento (um caracter ocupa 1 byte = 8 bits), tem-se:");
        int tamOriginal = frequenciaTotal*8;
        System.out.println("\tTamanho do arquivo pelo método convencional: "+tamOriginal+" bits");
        System.out.println("\tTamanho do arquivo pelo método de Huffman  : "+tamanhoFinal+" bits,");
        System.out.println("\tRESULTADO FINAL: "+(tamOriginal-tamanhoFinal)+ " bits a menos - redução de "+(((tamOriginal-tamanhoFinal)*100)/tamOriginal)+"%");
        System.err.print("\t------------------------------------\n");


        String quebraLinha = "\n";
        System.out.println("\nParte do texto original:\n");
        for (int i = 0; i < 400; i++){
            String aux3 = textoOriginal.get(i);

            if (!((textoOriginal.get(i).contains("¬")) || (textoOriginal.get(i).contains("¨")))){
                System.out.printf(textoOriginal.get(i));
            } else{
                if ((i>0 && textoOriginal.get(i-1).contains("¬")) && aux3.contains("¨")) System.out.printf(quebraLinha);
            }

        }


    }

}


