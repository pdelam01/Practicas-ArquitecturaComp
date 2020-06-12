#include "results.h"
#include "ui_results.h"

Results::Results(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Results)
{
    ui->setupUi(this);
}

Results::~Results()
{
    delete ui;
}

void Results::mostrarResultados(union Code op1, union Code op2, union Code result)
{
    vector<int> ope1 = convertToBinaryExpResult(op1.bitfield.expo, op1.bitfield.partFrac, op1.bitfield.sign);
    vector<int> ope2 = convertToBinaryExpResult(op2.bitfield.expo, op2.bitfield.partFrac, op2.bitfield.sign);

    if(!NaN){
        if(!inf && result.bitfield.expo < 255){
            vector<int> res = convertToBinaryExpResult(result.bitfield.expo, result.bitfield.partFrac, result.bitfield.sign);
            ui->lineEdit_11->setText(vectorToString(res));
            ui->lineEdit_19->setText(QString::number(result.numero));
            ui->lineEdit_7->setText("0x"+QString::number(result.numerox,16));
        }else{
            ui->lineEdit_11->setText("inf");
            ui->lineEdit_19->setText("inf");
            ui->lineEdit_7->setText("inf");
        }
    }else{
        ui->lineEdit_11->setText("NaN");
        ui->lineEdit_19->setText("NaN");
        ui->lineEdit_7->setText("NaN");
    }

    if(op1.bitfield.expo>254){
        ui->lineEdit_10->setText("inf");
        ui->lineEdit_9->setText("inf");
    }else{
        ui->lineEdit_10->setText(vectorToString(ope1));
        ui->lineEdit_9->setText("0x"+QString::number(op1.numerox,16));
    }

    if(op2.bitfield.expo>254){
        ui->lineEdit_12->setText("inf");
        ui->lineEdit_8->setText("inf");
    }else{
        ui->lineEdit_12->setText(vectorToString(ope2));
        ui->lineEdit_8->setText("0x"+QString::number(op2.numerox,16));
    }
}

QString Results::vectorToString(vector<int> oper)
{
    QString cad;
    for(int i=0; i<(int)oper.size(); i++){
        cad.append(QString::number(oper[i]));
    }
    return cad;
}

int Results::convertRealToUnion(float number, float number2, int op)
{
    inf = false;
    NaN = false;

    union Code op1;
    union Code op2;
    /* Convert the first number */
    op1.numero = number;
    op1.bitfield.sign;
    op1.bitfield.expo;
    op1.bitfield.partFrac;

    /* Convert the second number */
    op2.numero = number2;
    op2.bitfield.sign;
    op2.bitfield.expo;
    op2.bitfield.partFrac;

    switch (op) {
        case 0:{
            if(op1.bitfield.expo>=255 || op2.bitfield.expo>=255){
                /*inf*/
                total = 0.0;
                if(op1.numero==-op2.numero){
                    NaN = true;
                }else{
                    inf = true  ;
                }
            }else{
                if (op1.numero == 0) {
                    total = op2.numero;
                }else{
                    if (op2.numero == 0) {
                        total = op1.numero;
                    }else{
                        if(op1.numero!=-op2.numero){
                            vectorIEEE = operationAddition(op1, op2);
                            total = binaryToDecimal(vectorIEEE);
                        }else{
                            total = 0.0;
                        }
                    }
                }

            }
            break;
        }
        case 1:{
            if(op1.bitfield.expo>254){
                if (op2.bitfield.expo > 254) {
                    total = 0.0;
                    inf = true;
                }else{
                    if (op2.bitfield.expo == 0) {
                        total = 0.0;
                        NaN = true;
                    }
                }
            }else{
                if(op2.bitfield.expo>254){
                    if (op1.bitfield.expo > 254) {
                        total = 0.0;
                        inf = true;
                    }else{
                        if (op1.bitfield.expo == 0) {
                            total = 0.0;
                            NaN = true;
                        }
                    }
                }else{
                    vectorIEEE = operationProduct(op1, op2);
                    if(vectorIEEE[0]==2){
                        total = 0.0;
                        NaN = true;
                    }else{
                        vector<int> a = numberToBinary(0, 32);
                        bool equal = true;
                        for(int i=0; i< 32; i++){
                            if(vectorIEEE[i] != a[i]){
                                equal = false;
                            }
                        }
                        if(equal){
                            total = 0.0;
                        }else{
                            total = binaryToDecimal(vectorIEEE);
                        }
                    }
                }
            }
            break;
        }
        case 2:{

            if(op1.numero==0){
                if(op2.numero==0){
                    total = 0.0;
                    NaN = true;
                }else{
                   total = 0.0;
                }
            }else{
                if(op2.numero==0){
                    if(op1.numero==0){
                        total = 0.0;
                        NaN = true;
                    }else{
                       total = 0.0;
                       NaN=true;
                    }
                }else{
                    if (op1.bitfield.expo > 254) {
                        if (op2.numero == 0) {
                            total = 0.0;
                            NaN = true;
                        }else{
                            if (op2.bitfield.expo > 254) {
                                total=0.0;
                                NaN = true;
                            }else{
                                total = 0.0;
                                inf = true;
                            }
                        }
                    }else{
                        if(op1.numero == op2.numero){
                            total = 1.0;
                        }else{
                            if(op1.numero == -op2.numero){
                                total = -1.0;
                            }else{
                                vectorIEEE = operationDivision(op1, op2);
                                total = binaryToDecimal(vectorIEEE);
                            }
                        }
                    }
                }
            }
            break;
        }
        default:{
            return -1;
        }
    }

    /* Convert the total number */
    res.numero = total;
    res.bitfield.sign;
    res.bitfield.expo;
    res.bitfield.partFrac;

    mostrarResultados(op1,op2,res);

    cleanVectors();

    return 0;
}


vector<int> Results::operationAddition(union Code op1, union Code op2)
{

    /* Converts number to binary */
    /* STEP 0*/ /*DONE*/
    operator1 = convertToBinaryExp(op1.bitfield.expo, op1.bitfield.partFrac, op1.bitfield.sign);
    operator2 = convertToBinaryExp(op2.bitfield.expo, op2.bitfield.partFrac, op2.bitfield.sign);

    /*STEP 1*/ /*DONE*/ /*Inicializamos las variables*/

    int g = 0,r = 0, st = 0, d = 0;
    vector<int> p, _result;
    bool changed = false, complemented = false;
    c1=0;

    _result.resize(32);
    result.exponent.resize(8);


    /*STEP 2*/ /*DONE*/ /*Intercambiamos operadores*/

    if (op1.bitfield.expo < op2.bitfield.expo) {
        vector<int> aux;
        aux = operator1;
        operator1 = operator2;
        operator2 = aux;
        changed = true;
    }

    /*STEP 3*/ /*DONE*/ /*Calculamos d*/
    for (int i=0;i<8;i++) {
        result.exponent[i]= operator1[i+1];
    }

    if (changed) {
       d = op2.bitfield.expo - op1.bitfield.expo;
    }else{
       d = op1.bitfield.expo - op2.bitfield.expo;
    }


    /*STEP 4*/ /*DONE*/ /*Calculamos el complementoA2 de la mantisa de B*/

    if (operator1[0] != operator2[0]) {
        /*ComplementA2 of operator2*/
        vector<int> auxiliar;
        int counter = 0;

        for (int i = 9;i<(int)operator2.size();i++) {
            auxiliar.push_back(operator2[i]);
        }

        auxiliar = complement_A2(auxiliar);

        for (int i = 9;i<(int)operator2.size();i++) {
            operator2[i] = auxiliar[counter];
            counter++;
        }
    }

    /*STEP 5*/ /*DONE*/ /* Guardamos la mantisa de B */

    p = returnMantissa();

    /*STEP 6*/ /*DONE*/ /* Asignamos bit de guarda, bit de redondeo, bit sticky */

    if (d > 0 && d < 25) {
       g = p[d-1];
    }

    if (d > 1 && d < 26) {
       r = p[d-2];
    }

    if (d > 2 && d < 27) {
        int i=2;
        int sizeP = p.size();
        while ((d-i) > 0) {

            st = (st || p[sizeP-i]);
            i++;
        }
    }

    /*STEP 7*/ /*DONE*/ /* Desplazar P a la derecha introduciendo bits (1 o 0) */

    if (op1.bitfield.sign != op2.bitfield.sign) {
        if (d > 24) {

            for (int i = 0;i<(int)p.size();i++) {
                p[i]=1;
            }
        }else{
            if (d>0) {
               p = move1s(p,d);
            }
        }
    }else{
        if (d > 24) {
            p = numberToBinary(0,24);
        }else{
            if (d>0) {
               p = move0s(p,d);
            }
        }
    }

    c1=0;
    /*STEP 8*/ /*DONE*/ /* Sumamos a la mantisa A el acarreo */

    p = mantissaAddition(p);

    /*STEP 9*/ /*DONE*/ /* ComplementoA2 de P */

    if ((op1.bitfield.sign != op2.bitfield.sign) && (p[0]==1) && (c1 == 0)) {
        p = complement_A2(p);
        complemented=true;
    }

    /*STEP 10*/ /*DONE*/ /* Calculamos k bits para que P sea mantisa normalizada */

    if ((op1.bitfield.sign == op2.bitfield.sign) && (c1 == 1)) {

        int aug = g+r;

        if (aug == 2) {
            aug = 1;
        }
        aug += st;

        if (aug == 2) {
            aug = 1;
        }
        st = aug;

        r=p[23];


        p = moveNbits(1,true,p);

        p[0]=c1;

        c1 = 0;

        /*129 + 1*/
        result.exponent = vectorBinaryAddition(result.exponent, numberToBinary(1,8));

    } else {

        int k = 0,exit = 0;
        if (p[0]==0) {
            k++;
            while (exit == 0) {
                if (p[k] == 0) {
                    k++;
                }else{
                    exit = 1;
                }
            }
        }

        if (k == 0) {
            st = r || st;
            r=g;
        }

        if(k > 1){
            r=0;
            st=0;
        }

        int cont=0;
        /*Replace k bits*/
        for (int i = k; i <(int)p.size();i++) {
            p[cont] = p[i];
            cont++;
        }

        /*Fills with g's*/
        for (int i = cont;i<(int)p.size();i++) {
            p[i]=g;
        }

        int resta;

        if (changed) {
            resta = op2.bitfield.expo - k;
        }else{
            resta = op1.bitfield.expo - k;
        }

        result.exponent = numberToBinary(resta,8);

    }

    /*STEP 11*/ /*DONE*/ /* Redondeamos P */

    if ((r == 1 && st == 1) || (r == 1 && st == 0 && p[23] == 1)) {

        p = vectorBinaryAddition(p,numberToBinary(1,p.size()));
        int c2 = c1;

        if (c2 == 1) {

            /*Desplazar p , c2 bits a la derecha*/
            vector<int> aux;

            for (int i=0;i<(int)p.size();i++) {
                aux.push_back(p[i]);
            }

            int j=1;
            for (int i = 0; i <(int)p.size()-1;i++) {
               p[j] = aux[i];
               j++;
            }
            p[0]=c2;

            result.exponent = vectorBinaryAddition(result.exponent, numberToBinary(1,8));
        }
    }

    result.mantissa = p;

    /*STEP 12*/ /* Calculamos el signo del resultado */

    if (changed == false && complemented == true) {
        result.sign = op2.bitfield.sign;
    }else{
        if (changed) {
            result.sign = op2.bitfield.sign;
        }else{
            result.sign = op1.bitfield.sign;
        }
    }

    /*STEP 13*/ /* Devolvemos el resultado */


    _result.resize(32);

    result.partfracc.resize(23);
    result.mantissa.resize(24);

    _result[0] = result.sign;

    for (int i = 0;i< (int)result.exponent.size();i++) {
        _result[i+1]=result.exponent[i];
    }

    int partFracc=0;
    for (int i = 1;i<(int)result.mantissa.size();i++) {
        result.partfracc[partFracc]=result.mantissa[i];
        _result[i+8]=result.mantissa[i];
        partFracc++;
    }


    return _result;
}

vector<int> Results::operationProduct(union Code op1, union Code op2)
{
    c1 = 0;
    vector<int> salida;
    salida.resize(32);

    if(op1.numero == 0) {
        if(op2.bitfield.expo>254 || op2.bitfield.expo<0){
            /*NaN*/
            salida[0] = 2;
            return salida;
        }else{
            /*0*/
            for(int i=0; i<32; i++){
                salida[0] = 0;
            }
            return salida;
        }
    }

    if(op2.numero == 0) {
        if(op1.bitfield.expo>254 || op1.bitfield.expo<0){
            /*NaN*/
            salida[0] = 2;
            return salida;
        }else{
            /*0*/
            for(int i=0; i<32; i++){
                salida[0] = 0;
            }
            return salida;
        }
    }

    int r = 0, st = 0;
    operator1 = convertToBinaryExp(op1.bitfield.expo, op1.bitfield.partFrac, op1.bitfield.sign);
    operator2 = convertToBinaryExp(op2.bitfield.expo, op2.bitfield.partFrac, op2.bitfield.sign);

    /*STEP 1*/
    if(op1.bitfield.sign == 0){
        if(op2.bitfield.sign == 0){
            result.sign = 0;
        }else{
            result.sign = 1;
        }
    }else{
        if(op2.bitfield.sign == 1){
            result.sign = 0;
        }else{
            result.sign = 1;
        }
    }

    /*STEP 2*/
    int auxExponente1 = op1.bitfield.expo - 127;
    int auxExponente2 = op2.bitfield.expo - 127;
    int exponente = auxExponente1+auxExponente2+127;
    result.exponent = numberToBinary(exponente, 8);

    /*STEP 3*/
    vector<int> p, mantA, mantB;
    mantA.resize(24);
    mantB.resize(24);
    int countMantisa = 9;
    for(int i=0; i<24; i++){
        mantA[i]=operator1[countMantisa];
        mantB[i]=operator2[countMantisa];
        countMantisa++;
    }

    c1 = 0;
    /*3.I Producto sin signo*/
    p = binaryProductWithoutSign(mantA, mantB);

    c1 = 0;
    /*3.II Desplazar*/
    if(p[0] == 0){

        p = moveNbits(1, false, p);
        p[47] = 0;
    }else{
        exponente++;
        result.exponent = numberToBinary(exponente, 8);
    }

    /*3.III Bit de redondeo*/
    r = p[24];

    /*3.IV Bit de Sticky*/
    for(int i=24; i<48; i++){
        st = st||p[i];
    }
     /*3.V Redondeo*/
    if((r==1 && st==1) || (r==1 && st==0 && p[23]==1)){
        vector<int> aux;
        aux.resize(24);
        for(int i=0; i<24; i++){
            aux[i] = p[i];
        }
        aux = vectorBinaryAddition(aux, numberToBinary(1,24));
        for(int i=0; i<24; i++){
            p[i] = aux[i];
        }
    }

    int t = overflowProduct(exponente);
    /* Interpretamos el valor de t */
    switch (t) {

    case -1:
        /* inf */
        inf = true;
        return p;
    case -2:
        /* NaN */
        NaN = true;
        return p;
    case 0:
        break;
    case 1:
        p = moveNbits(t, true, p);
        for(int i=0; i<t; i++){
            p[i] = 0;
        }

        exponente = 1;

        result.exponent[0] = 0;
        for(int i=1; i<8; i++){
            result.exponent[i] = 1;
        }
        break;

    default:
        /*ERROR*/
        return p;
    }

    result.mantissa.resize(24);
    result.partfracc.resize(23);
    for(int i=0; i<24; i++){
        result.mantissa[i] = p[i];
    }

    vector<int> _result;
    _result.resize(32);

    _result[0] = result.sign;

    for (int i = 0;i< (int)result.exponent.size();i++) {
        _result[i+1]=result.exponent[i];
    }


    int partFracc=0;
    for (int i = 1;i<(int)result.mantissa.size();i++) {
        result.partfracc[partFracc]=result.mantissa[i];
        _result[i+8]=result.mantissa[i];
        partFracc++;
    }

    return _result;
}


vector<int> Results::operationDivision(union Code op1, union Code op2)
{
    /*
    *
    * STEP 0. INICIALIZACIÓN DE OPERANDOS Y VARIABLES
    *
    */
    vector<int> o1 = convertToBinaryExp(op1.bitfield.expo, op1.bitfield.partFrac, op1.bitfield.sign);
    vector<int> o2 = convertToBinaryExp(op2.bitfield.expo, op2.bitfield.partFrac, op2.bitfield.sign);

    double bp = 0.0, xo = 0.0, yo = 0.0;


    /*
    *
    * STEP 1. ESCALADO DE A Y B
    *
    */

    /*Creo dos vectores de 24 bits para la mantisa*/
    vector<int> op1escalado,op2escalado;

    op1escalado.resize(24);
    op2escalado.resize(24);
    int count = 0;

    /*Del numero en binario cojo la mantisa*/
    for (int i = 9;i<(int)o1.size();i++) {
        op1escalado[count]=o1[i];
        op2escalado[count]=o2[i];
        count++;
    }

    /*Escalo los vectores a decimal*/
    double escalado1 = mantissaToDecimal(op1escalado);
    double escalado2 = mantissaToDecimal(op2escalado);

    /*
    *
    * STEP 2. BUSCAR EN EL TABLA B' EN LOS INTERVALOS [1, 1.25)
    *                                                 [1.25, 2)
    */

    if (escalado2 >=1.0 && escalado2 < 1.25) {
        bp = 1.0;
    }else{
        bp = 0.8;
    }

    /*
    *
    * STEP 3. ASIGNAR Xo e Yo
    *
    */

    union Code auxoperator1, auxoperator2;
    auxoperator1.numero = escalado1;
    auxoperator2.numero = bp;

    xo = binaryToDecimal(operationProduct(auxoperator1, auxoperator2));

    auxoperator1.numero = escalado2;

    yo = binaryToDecimal(operationProduct(auxoperator1, auxoperator2));

    /*
    *
    * STEP 4. ITERAR HASTA QUE X(i+1) - Xi < 10^-4
    *
    */
    double resta = 1.0,xAux=0.0;
    double r = 0.0;
    vector<int> temp;
    temp.resize(32);

    while (abs(resta) > 0.0001) {
       xAux=-xo;
       /* r = 2 - yo */
       auxoperator1.numero=2;
       auxoperator2.numero=-yo;

       temp = operationAddition(auxoperator1, auxoperator2);
       r = binaryToDecimal(temp);

       /* yo = yo * r */
       auxoperator1.numero=yo;
       auxoperator2.numero=r;
       temp = operationProduct(auxoperator1, auxoperator2);
       yo = binaryToDecimal(temp);

       /* xo = xo * r */
       auxoperator1.numero=xo;
       temp = operationProduct(auxoperator1, auxoperator2);
       xo = binaryToDecimal(temp);

       /* x1 - xo */
       auxoperator1.numero = xo;
       auxoperator2.numero = xAux;

       resta = binaryToDecimal(operationAddition(auxoperator1, auxoperator2));

    }

    auxoperator1.numero = xo;

    vector<int> aproximacion = convertToBinaryExp(auxoperator1.bitfield.expo, auxoperator1.bitfield.partFrac, auxoperator1.bitfield.sign);

    /* Cáclculo del SIGNO de la división */
    int sign;
    if (o1[0] != o2[0]) {
        sign = 1;
    }else{
        sign = 0;
    }

    /*Cálculo del EXPONENTE de la división*/

    int cuadrado=7,exponenteAB=0, exponenteDiv;

    for (int i = 1;i<9;i++) {
        exponenteAB += aproximacion[i]*pow(2,cuadrado);
        cuadrado--;
    }

    auxoperator1.numero = op1.bitfield.expo;
    auxoperator2.numero = -op2.bitfield.expo;
    exponenteDiv = binaryToDecimal(operationAddition(auxoperator1, auxoperator2));

    auxoperator1.numero = exponenteDiv;
    auxoperator2.numero = exponenteAB;
    exponenteDiv = binaryToDecimal(operationAddition(auxoperator1, auxoperator2));

    if(exponenteDiv>254){
        inf = true;
    }

    vector<int> temporal;
    temporal = numberToBinary(exponenteDiv,8);

    /* Devolvemos el resultado */


   vector<int> _result;
   _result.resize(32);

   _result[0] = sign;

   for (int i = 0;i< (int)result.exponent.size();i++) {
       _result[i+1]=temporal[i];
   }

   for (int i = 9;i<(int)aproximacion.size();i++) {
       _result[i]=aproximacion[i+1];
   }

   return _result;
}

vector<int> Results::convertToBinaryExp(int number, int pf, int sign)
{

    vector<int> exit;
    exit.resize(33);

    exit[0]=sign;

    if(pf==127){
        for(int i=8; i>0; i--){
            if (i != 8) {
                exit[i]=0;
            } else {
                exit[i]=1;
            }
        }

        //Este es el 0 de la mantisa
        exit[9] = 0;

        for(int i=32; i>9; i--){
            if (pf%2 == 0) {
                exit[i]=0;
            } else {
                exit[i]=1;
            }
            pf = (int) pf/2;
        }

    }else{
        for(int i=8; i>0; i--){
            if (number%2 == 0) {
                exit[i]=0;
            } else {
                exit[i]=1;
            }
            number = (int) number/2;
        }
        // Este es el 1 de la mantisa
        exit[9]=1;

        for(int i=32; i>9; i--){
            if (pf%2 == 0) {
                exit[i]=0;
            } else {
                exit[i]=1;
            }
            pf = (int) pf/2;
        }
    }

   return exit;
}

vector<int> Results::convertToBinaryExpResult(int number, int pf, int sign)
{

    vector<int> exit;
    exit.resize(32);

    exit[0]=sign;

    if(pf==127){
        for(int i=8; i>0; i--){
            if (i != 8) {
                exit[i]=0;
            } else {
                exit[i]=1;
            }
        }

        for(int i=31; i>8; i--){
            if (pf%2 == 0) {
                exit[i]=0;
            } else {
                exit[i]=1;
            }
            pf = (int) pf/2;
        }

    }else{
        for(int i=8; i>0; i--){
            if (number%2 == 0) {
                exit[i]=0;
            } else {
                exit[i]=1;
            }
            number = (int) number/2;
        }

        for(int i=31; i>8; i--){
            if (pf%2 == 0) {
                exit[i]=0;
            } else {
                exit[i]=1;
            }
            pf = (int) pf/2;
        }
    }

   return exit;
}

vector<int> Results::complement_A2(vector<int> vec)
{
    for (int i=0;i<(int)vec.size();i++) {
        if (vec[i]==0) {
            vec[i]=1;
        }else{
            vec[i]=0;
        }
    }

    vector<int> one = numberToBinary(1,vec.size());
    vec = vectorBinaryAddition(vec, one);

    return vec;
}

vector<int> Results::complement_A1(vector<int> vec)
{
    for (int i=0;i<(int)vec.size();i++) {
        if (vec[i]==0) {
            vec[i]=1;
        }else{
            vec[i]=0;
        }
    }
    return vec;
}
vector<int> Results::returnMantissa()
{
    vector<int> aux;

    for (int i= 9;i<(int)operator2.size(); i++) {
        aux.push_back(operator2[i]);
    }

    return aux;
}

vector<int> Results::move0s(vector<int> pe, int de)
{
    vector<int> aux;
    aux.resize(24);
    int count = 0;

    for (int i=0;i<de;i++) {
        aux[i]=0;
    }

    for (int i=de;i<(int)pe.size();i++) {
        aux[i]=pe[count];
        count++;
    }

    return aux;
}

vector<int> Results::move1s(vector<int> pe, int de)
{
    vector<int> aux;
    aux.resize(24);
    int count = 0;

    for (int i=0;i<de;i++) {
        aux[i]=1;
    }

    for (int i=de;i<(int)pe.size();i++) {
        aux[i]=pe[count];
        count++;
    }

    return aux;
}

vector<int> Results::mantissaAddition(vector<int> pe)
{

    vector<int> mantA;
    int resul;

    for (int i = 9;i<33; i++) {
        mantA.push_back(operator1[i]);
    }

    for (int i = (int)mantA.size()-1;i>=0;i--) {
        resul = mantA[i]+pe[i];

        if (c1 == 1) {
            switch (resul) {
                case 0:
                    pe[i]=1;
                    c1=0;
                    break;

                case 1:
                    pe[i]=0;
                    c1=1;
                    break;
                case 2:
                    pe[i]=1;
                    c1=1;
                    break;
            }

        }else{
            switch (resul) {
                case 0:
                    pe[i]=0;
                    c1=0;
                    break;

                case 1:
                    pe[i]=1;
                    c1=0;
                    break;

                case 2:
                    pe[i]=0;
                    c1=1;
                    break;
            }
        }
    }

    return pe;
}

vector<int> Results::vectorBinaryAddition(vector<int> a, vector<int> b)
{
    int r;
    int ac = c1;

    for (int i = (int)a.size()-1;i>=0;i--) {
        r = a[i]+b[i];

        if (ac == 1) {
            switch (r) {
                case 0:
                    a[i]=1;
                    ac=0;
                    break;

                case 1:
                    a[i]=0;
                    ac=1;
                    break;

                case 2:
                    a[i]=1;
                    ac=1;
                    break;
            }

        }else{
            switch (r) {
                case 0:
                    a[i]=0;
                    ac=0;
                    break;

                case 1:
                    a[i]=1;
                    ac=0;
                    break;

                case 2:
                    a[i]=0;
                    ac=1;
                    break;
            }
        }
    }

    c1 = ac;

    return a;
}

vector<int> Results::numberToBinary(int n, int size)
{
    vector<int> exit;
    exit.resize(size);

    for(int i=(int)exit.size()-1; i>=0; i--){
        if (n%2 == 0) {
            exit[i]=0;
        } else {
            exit[i]=1;
        }
        n = (int) n/2;
    }

    return exit;
}

vector<int> Results::moveNbits(int n, bool derecha, vector<int> vec)
{
    vector<int> aux;
    int veccount = 0;
    aux.resize(vec.size());
    if (derecha) {

        for (int i=n;i<(int)vec.size();i++) {
            aux[i]=vec[veccount];
            veccount++;
        }

    }else{

        for (int i=n;i<(int)vec.size();i++) {
            aux[veccount]=vec[i];
            veccount++;
        }
    }

    return aux;
}

double Results::binaryToDecimal(vector<int> vec)
{
    double total=0;
    int expo=7;

    int suma = 0;
    for (int i=1 ;i<=8;i++) {
        suma += vec[i]*pow(2,expo);
        expo--;
    }

    suma = suma - 127;

    vector<int> num;
    int aux=0;
    expo = suma;

    for (int i = (int)vec.size()-1;i>=0;i--) {
        if (vec[i] == 1) {
            aux = i;
            break;
        }
    }

    num.push_back(1);

    for (int i = 9;i <= aux;i++) {
        num.push_back(vec[i]);
    }

    for (int i = 0;i < (int)num.size() ;i++) {
        total += num[i]*pow(2,expo);
        expo--;
    }


    if (vec[0] == 1) {
       total = -total;
    }

    return total;

}

vector<int> Results::binaryProductWithoutSign(vector<int> mantA, vector<int> mantB)
{
    vector<int> p;
    p.resize(24);
    vector<int> result;
    result.resize(48);
    for(int i=0; i<24; i++){
        p[i] = 0;
    }

    for(int i=0; i<24; i++){
        c1 = 0;
        if(mantA[23]==1){
            p = vectorBinaryAddition(p, mantB);
        }

        int auxForMove = p[23];

        p = moveNbits(1, true, p);
        p[0] = c1;

        mantA = moveNbits(1, true, mantA);
        mantA[0] = auxForMove;
    }

    for(int i=0; i<24; i++){
       result[i] = p[i];
    }

    int count = 0;
    for(int i=24; i<48; i++){
       result[i] = mantA[count];
       count++;
    }

    return result;

}

int Results::overflowProduct(int exponente)
{  

    if(exponente > 254){
        /* Overflow */
        return -1;
    }

    if(exponente<1){
        int t = 1-exponente;
        if(t>=24){
            /* Underflow */
            return -2;
        }else{
            /*Numero denormal*/
            return 1;
        }
    }
    return 0;
}

double Results::mantissaToDecimal(vector<int> mant)
{
    int expo=0;

    double suma = 0.0;
    for (int i=0 ;i<(int)mant.size();i++) {
        suma += mant[i]*pow(2,expo);
        expo--;
    }

    return suma;
}

void Results::cleanVectors()
{
    result.exponent.clear();
    result.mantissa.clear();
    result.partfracc.clear();

    operator1.clear();
    operator2.clear();

    inf = false;
    NaN = false;
}
