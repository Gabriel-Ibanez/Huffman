public class Nodo {
    String caracter = "";
    String filho0 = "";
    String filho1 = "";
    int f = -1;
    int p = -1; //posição;

    public Nodo(String caracter, String filho0, String filho1, int f, int p) {
        this.caracter = caracter;
        this.filho0 = filho0;
        this.filho1 = filho1;
        this.f = f;
        this.p = p;
    }

    public String getCaracter() {
        return caracter;
    }

    public void setCaracter(String caracter) {
        this.caracter = caracter;
    }

    public String getFilho0() {
        return filho0;
    }

    public void setFilho0(String filho0) {
        this.filho0 = filho0;
    }

    public String getFilho1() {
        return filho1;
    }

    public void setFilho1(String filho1) {
        this.filho1 = filho1;
    }

    public int getF() {
        return f;
    }

    public void setF(int f) {
        this.f = f;
    }

    public int getP() {
        return p;
    }

    public void setP(int p) {
        this.p = p;
    }
}
