#include "principal.h"
vector<Professor> Principal::professor; // vetor de professores a serem lidos na tabela
vector<Turma> Principal::turmas; // vetor de turmas a ser lido na tabela
Horario Principal::horario[nh][ndia]; // vetor de horarios a ser lido na tabela
vector<Disciplina> Principal::disc; // vetor de disciplina a ser lido na tabela
Ant Principal::formigas[na]; // vetor de formigas
vector<Turma> Principal::turmasUtilizadas;
vector<vector<int> > Principal::solucaoFinal;



Principal::Principal(){
}

void Principal::leituraArquivo(char*arq1,char*arq2,char*arq3){
    cout << "Lendo arquivos de entrada..." << endl;
    char read[tam];

    ifstream arqi(arq1);
    if(arqi.fail())
    {
        cout << "\n\nERRO 01\n\n" << endl;
        exit(1);
    }
    arqi.ignore(ign,'\n'); // Leitura das disciplinas e preferências dos professores
    arqi.ignore(ign,'\n');
    arqi.ignore(tam,';');
    arqi.get(read,tam,';');
    for(int b = 0;b < Constantes::getNumeroProf();b++){
        Professor *prof = new Professor();
        professor.push_back(*prof);
    }
    for(int b = 0;b < Constantes::getNumeroDisc();b++){
        Disciplina *disciplina = new Disciplina();
        disc.push_back(*disciplina);
    }
    for(int b = 0;b < Constantes::getNumeroTurmas();b++){
        Turma *turma = new Turma();
        turmas.push_back(*turma);
    }

    for(int a = 0;strcmp(read,"") != 0;a++)
    {

        if(a == Constantes::getNumeroDisc())
        {
            cout << "\n\nERRO 05\n\n" << endl;
            exit(5);
        }
        disc[a].codigo = operacoes::convert(read);
        arqi.get();
        arqi.get(read,tam,';');
        disc[a].nome = read;
        arqi.get();
        for(int b = 0;b < 4;b++)
            arqi.ignore(tam,';');
        for(int b = 0;b < Constantes::getNumeroProf();b++)
        {
            arqi.get(read,tam,';');
            professor[b].SetPrefD(operacoes::convert(read), a);
            arqi.get();
        }

        arqi.get(read,tam,';');
        disc[a].tipo = operacoes::convert(read);
        arqi.get();
        arqi.get(read,tam,';');
        disc[a].qtdCreditos = operacoes::convert(read);
        arqi.get();
        arqi.get(read,tam,';');
        disc[a].area = operacoes::convert(read);
        arqi.get();

        arqi.get(read,tam,'\n');
        switch (atoi(read)){
            case 0: disc[a].horarioFixo = false;
                break;
            case 1: disc[a].horarioFixo = true;
                break;
            default: cout << "\n\nERRO AO SETAR HORARIO FIXO A DISCIPLINA\n\n" << endl;
                break;
        }
        arqi.get();

        arqi.ignore(tam,';');
        arqi.get(read,tam,';');

    }
    arqi.close();

    for(int a = 0;a < Constantes::getNumeroProf();a++) // Define a matrícula dos professores
        professor[a].SetSiap(a+1);

    arqi.open(arq2);
    if(arqi.fail())
    {
        cout << "\n\nERRO 02\n\n" << endl;
        exit(2);
    }
    arqi.ignore(ign,'\n'); // Leitura das turmas
    arqi.get(read,tam,';');
    for(int a = 0;strcmp(read,"") != 0;a++)
    {
        turmas[a].disc = operacoes::convert(read);
        arqi.get();
        arqi.get(read,tam,';');
        turmas[a].codigo[0] = read[0];
        turmas[a].codigo[1] = read[1];
        turmas[a].codigo[2] = read[2];
        arqi.get();
        arqi.get(read,tam,';');
        arqi.get();
        arqi.get(read,tam,';');        
        turmas[a].h1.dia = read;
        arqi.get();
        arqi.get(read,tam,';');
        turmas[a].h1.hora = operacoes::convert(read);
        arqi.get();


        const char *dia = turmas[a].h1.dia.c_str();
        int diaNum = atoi(dia);
        switch(diaNum)
        {
            case 2: turmas[a].h1.horaSemanal = turmas[a].h1.hora - 8;
                break;
            case 3: turmas[a].h1.horaSemanal = 15 + turmas[a].h1.hora - 8;
                break;
            case 4: turmas[a].h1.horaSemanal = 30 + turmas[a].h1.hora - 8;
                break;
            case 5: turmas[a].h1.horaSemanal = 45 + turmas[a].h1.hora - 8;
                break;
            case 6: turmas[a].h1.horaSemanal = 60 + turmas[a].h1.hora - 8;
                break;
            case 7: turmas[a].h1.horaSemanal = 75 + turmas[a].h1.hora - 8;
                break;
            default: cout << "\n\nERRO AO SETAR O DIA SEMANAL\n\n" << endl;
                exit(1);
        }
        arqi.get(read,tam,';');
        turmas[a].h2.dia = read;
        arqi.get();
        arqi.get(read,tam,'\n');
        turmas[a].h2.hora = operacoes::convert(read);

        dia = turmas[a].h2.dia.c_str();
        diaNum = atoi(dia);

        switch(diaNum)
        {
            case 0: turmas[a].h2.horaSemanal = -1;
                break;
            case 2: turmas[a].h2.horaSemanal = turmas[a].h2.hora - 8;
                break;
            case 3: turmas[a].h2.horaSemanal = 15 + turmas[a].h2.hora - 8;
                break;
            case 4: turmas[a].h2.horaSemanal = 30 + turmas[a].h2.hora - 8;
                break;
            case 5: turmas[a].h2.horaSemanal = 45 + turmas[a].h2.hora - 8;
                break;
            case 6: turmas[a].h2.horaSemanal = 60 + turmas[a].h2.hora - 8;
                break;
            case 7: turmas[a].h2.horaSemanal = 75 + turmas[a].h2.hora - 8;
                break;
            default: cout << "\n\nERRO AO SETAR O DIA SEMANAL\n\n" << endl;
                exit(1);
        }

        arqi.get();
        arqi.get(read,tam,';');
        for(int b = 0;b < Constantes::getNumeroDisc();b++)
        {
            if(turmas[a].disc == disc[b].codigo)
            {
                turmas[a].indDisc = b;
                break;
            }
        }
        if(turmas[a].indDisc == -1) // Encontrou turma cuja disciplina não estava no arquivo entrada1.csv
        {
            cout << "\n\nERRO 06\n\n" << endl;
            exit(6);
        }
    }
    arqi.close();

    arqi.open(arq3);
    if(arqi.fail())
    {
        cout << "\n\nERRO 03\n\n" << endl;
        exit(3);
    }
    arqi.ignore(ign,'\n');// Leitura dos cargos dos professores
    arqi.ignore(ign,'\n');
    for(int a = 0;a < Constantes::getNumeroProf();a++)
    {
        arqi.ignore(ign,';');
        arqi.get(read,tam,';');
        professor[a].SetCargo(operacoes::convert(read));
        arqi.get();
//        arqi.get(read,tam,';');
//        if(operacoes::convert(read) > professor[a].GetCargo())
//            professor[a].SetCargo(operacoes::convert(read));
//        arqi.get();
        arqi.ignore(ign,'\n');
    }
    arqi.close();
}

void Principal::inicializaHoras(){
    int hora=0, horastrabalhadas = 0, m;
    for(int i=0;i<Constantes::getNumeroProf();i++){
        for(m=0;m<nh;m++){
            if(rand()%2 == 1 && hora < 8 && horastrabalhadas < 40){ // tenta colocar no maximo 8 horas por dia para o professor
                professor[i].SetPrefH(1, m);
                hora++;
                horastrabalhadas++;
            }
            if(nh%15 == 0){
                hora = 0;
            }
        }
        while(horastrabalhadas < 40){ // caso nao consegue ele coloca mais até dar um total de 40 horas semanais
            m = rand()%nh;
            if(professor.at(i).GetPrefH(m) == 0){
                professor.at(i).SetPrefH(1, m);
                horastrabalhadas++;
            }
        }
        horastrabalhadas = 0;
    }
}

void Principal::run(Turma turma[], int numeroTurma, char *resultado){

    int numeroProf = Constantes::getNumeroProf();
    int numeroDisc = Constantes::getNumeroDisc();
    double wt[numeroProf][2]; // vetor omega de turmas e de horas, onde 0 é o nivel de feromonios e 1 é a posição em que ela estava inicialmente
    double wh[nh][2], wh2[nh][2];
    int turmaAlocada = 0, iatual=0; // controle de quantas turmas ja foram alocadas e o indice de interações atualmente
    int numtentativasT = 0, numtentativasH = 0;// vezes em que se tentou criar uma solução
    int maxDiag = 0; // controle para a matriz imaginaria passar sempre na diagonal
    int freeze = 0, freeze2 = 0; // conta quantas vezes a solução nao muda
    double bestDFTAtual=10000, bestDFTGlobal = 10000; // melhor dft atualmente(desconsiderando o global)
    Professor prof[numeroProf];
    Disciplina disciplina[numeroDisc];


    for(int i=0;i<numeroProf;i++){
        prof[i] = professor.at(i);
    }
    for(int i=0;i<numeroDisc;i++){
            disciplina[i] = disc.at(i);
        }

    Ant::inicializa(prof,turma,numeroTurma); // incializa os feromonios

    for(int i=0;i<na;i++)
        formigas[i].inicializaSolucao(numeroTurma);


    while(iatual<imax){ // inicia o loop principal
        for(int g=0;g<na;g++){ // constroi e gera as soluções
            while(turmaAlocada < numeroTurma){ //enquanto há turmas sem professor ele acha um professor para ela
                for(int i=0;i<numeroProf;i++){ // copiar para o vetor wh todos os professores posiveis para determinada disciplina, fazendo com que passe disciplina por disciplina para achar um professor correspondente
                    wt[i][0] = formigas[g].getFeromoniosT(i,turmaAlocada);
                    wt[i][1] = i;
                }

                operacoes::getNextPermItemT(wt, numtentativasT, numeroProf); // usa o nextPermItem para ordenar o vetor de uma forma randomica

                if(disciplina[turma[turmaAlocada].indDisc].horarioFixo==false){
                    for(int i=0;i<nh;i++){ // irá buscar todas os horarios possiveis do professor em que o nextPermItem retornou e tentar achar um horario para ele
                        wh[i][0] = formigas[g].getFeromoniosH(wt[numtentativasT][1],i);
                        wh[i][1] = i;
                    }

                    operacoes::getNextPermItemH(wh, numtentativasH, nh); // usa o nextPermItem para retornar um horario adequado

                    if(disciplina[turma[((int)wt[numtentativasT][1])].indDisc].qtdCreditos==4){
                        for(int i=0;i<nh;i++){ // irá buscar todas os horarios possiveis do professor em que o nextPermItem retornou e tentar achar um horario para ele
                            wh2[i][0] = Ant::getFeromoniosH(wt[numtentativasT][1],i);
                            wh2[i][1] = i;
                        }

                        operacoes::getNextPermItemH2(wh2, numtentativasH, nh, static_cast<int>(wh[numtentativasH][1])); // usa o nextPermItem para retornar um horario adequado
                    }

                    else{
                        wh2[numtentativasH][0] = -1;
                    }


                    if((!disciplina[numeroTurma].horarioFixo) && (operacoes::validasolucao(formigas[g], prof[static_cast<int>(wt[numtentativasT][1])], static_cast<int>(wh[numtentativasH][1]), static_cast<int>(wh2[numtentativasH][1]),numeroTurma))){ // confere se a solução é uma solução valida, se sim dimunui o numero de disciplinas alocadas e seta essa solução
                        formigas[g].setSolucao(wt[numtentativasT][1], turmaAlocada, 0);
                        formigas[g].setSolucao((((int)wh[numtentativasH][1])), turmaAlocada, 1);
                        formigas[g].setSolucao((((int)wh2[numtentativasH][1])), turmaAlocada, 2);
                        formigas[g].setSolucao(turma[turmaAlocada].indDisc, turmaAlocada, 3);
                        for(int i=0;i<Principal::turmasUtilizadas.size();i++){
                            Turma t = turmasUtilizadas.at(i);
                            if((turma[turmaAlocada].disc == t.disc)&&(turma[turmaAlocada].codigo[0] == t.codigo[0])&&(turma[turmaAlocada].codigo[1] == t.codigo[1])&&(turma[turmaAlocada].codigo[2] == t.codigo[2])){
                                formigas[g].setSolucao(i, turmaAlocada, 4);
                                break;
                            }
                        }

                        // reseta as variaveis de controle e aumenta o número de turma alocada
                        turmaAlocada++;
                        numtentativasT=0;
                        numtentativasH=0;
                        maxDiag = 0;
                        operacoes::setPosT(0);
                        operacoes::setPosH(0);
                        operacoes::setPosH2(0);

                    }
                }

                else if(operacoes::validasolucao(formigas[g], prof[static_cast<int>(wt[numtentativasT][1])], turma[turmaAlocada].h1.horaSemanal, turma[turmaAlocada].h2.horaSemanal,numeroTurma)){ // confere se a solução é uma solução valida, se sim dimunui o numero de disciplinas alocadas e seta essa solução
                    formigas[g].setSolucao(wt[numtentativasT][1], turmaAlocada, 0);
                    formigas[g].setSolucao(turma[turmaAlocada].h1.horaSemanal, turmaAlocada, 1);
                    formigas[g].setSolucao(turma[turmaAlocada].h2.horaSemanal, turmaAlocada, 2);
                    formigas[g].setSolucao(turma[turmaAlocada].indDisc, turmaAlocada, 3);
                    for(int i=0;i<Principal::turmasUtilizadas.size();i++){
                        Turma t = turmasUtilizadas.at(i);
                        if((turma[turmaAlocada].disc == t.disc)&&(turma[turmaAlocada].codigo[0] == t.codigo[0])&&(turma[turmaAlocada].codigo[1] == t.codigo[1])&&(turma[turmaAlocada].codigo[2] == t.codigo[2])){
                            formigas[g].setSolucao(i, turmaAlocada, 4);
                            break;
                        }
                    }

                    // reseta as variaveis de controle e aumenta o número de turma alocada
                    turmaAlocada++;
                    numtentativasT=0;
                    numtentativasH=0;
                    maxDiag = 0;
                    operacoes::setPosT(0);
                    operacoes::setPosH(0);
                    operacoes::setPosH2(0);

                }

                else{ // aumenta o numero de tentativas para o getNestxPermItem recriar uma nova possivel solução e garante que ele sempre vai percorrer a matriz de forma diagonal
                    if(numtentativasT == numeroProf || numtentativasH == nh){
//                        numtentativasT =0;
//                        numtentativasH =0;
                        cout<<"ERRO 13";
                        exit(13);
                    }
                    if(maxDiag == numtentativasT || numtentativasH==0){
                        maxDiag++;
                        numtentativasH = maxDiag;
                        numtentativasT = 0;
                    }
                    else{
                        numtentativasT++;
                        numtentativasH--;
                    }

                }

            }
            // classifica a solução encontrada
            formigas[g].setDTF(operacoes::classificaHC(formigas[g], prof, disciplina, numeroTurma, numeroProf));
            formigas[g].setSCP(operacoes::classificaSC(formigas[g], prof, numeroTurma, numeroProf));
            turmaAlocada=0;

        }

        //////////////////////////// atualização dos feromônios

        Solucoes solucoes[na]; //vetor que contem todas as soluções encontradas na iteração atual, onde 0 é a formiga que achou a solução, 1 é o DFT da soçução, e 2 é o SCP da solução

        for(int x=0;x<na;x++){ // salva em um  vetor auxiliar a pontuação e todas as soluções e qual formiga tem essa pontuação
            solucoes[x].formigas = x;
            solucoes[x].DFT = formigas[x].getDTF();
            solucoes[x].SCP = formigas[x].getSCP();
        }

        int aux1=0;
        double aux=0; // auxiliar para ordenar o vetor de soluções
        for(int x=0; x<na;x++){ // ordena o vetor por DFT
            for(int t=x;t<na;t++){
                if(solucoes[x].DFT > solucoes [t].DFT){
                    aux1 = solucoes[x].formigas;
                    solucoes[x].formigas = solucoes[t].formigas;
                    solucoes[t].formigas = aux1;

                    aux = solucoes[x].DFT;
                    solucoes[x].DFT = solucoes[t].DFT;
                    solucoes[t].DFT = aux;

                    aux = solucoes[x].SCP;
                    solucoes[x].SCP = solucoes[t].SCP;
                    solucoes[t].SCP = aux;

                    if(solucoes[x].DFT == solucoes [t].DFT && solucoes[x].SCP > solucoes [t].SCP){ // após ele estar ordenado por DFT ele tenta ordenar também por SCP
                        aux1 = solucoes[x].formigas;
                        solucoes[x].formigas = solucoes[t].formigas;
                        solucoes[t].formigas = aux1;

                        aux = solucoes[x].DFT;
                        solucoes[x].DFT = solucoes[t].DFT;
                        solucoes[t].DFT = aux;

                        aux = solucoes[x].SCP;
                        solucoes[x].SCP = solucoes[t].SCP;
                        solucoes[t].SCP = aux;
                    }

                }
            }
        }

        double f=0; // f e g sao parametros para se atualizar o numero de feromonios
        double g=0;
        double At=0; // delta tau
        double nAt=0; // negação para o delta tau

        for (int i=0;i<10;i++){ // aumenta o nivel de feromonios para as 10 melhores soluções

            // calculo do f
            if(solucoes[i].DFT == 0)
                f = 200;
            else
                f = 100/solucoes[i].DFT;

            // calculo do g
            if(solucoes[i].SCP == 0)
                g = 2000;
            else
                g = 1000/solucoes[i].SCP;


            At = f*g; // formula para calcular o delta tau

            for(int j=0;j<numeroTurma;j++){ // calcula e aumenta o numero de feromonios
                int k = formigas[solucoes[i].formigas].getSolucao(j,0);
                nAt = (1-pow((1-y),operacoes::classificaElementoSC(formigas[solucoes[i].formigas], prof[k], j, numeroTurma)))*f*g;
                formigas[solucoes[i].formigas].setFeromoniosT(formigas[solucoes[i].formigas].getFeromoniosT(k, j)+At-nAt, k, j);
                formigas[solucoes[i].formigas].setFeromoniosH(formigas[solucoes[i].formigas].getFeromoniosH(k, formigas[solucoes[i].formigas].getSolucao(j,1))+At-nAt, k, formigas[solucoes[i].formigas].getSolucao(j,1));
//                formigas[((int)solucoes[i][0])].setFeromoniosH(formigas[((int)solucoes[i][0])].getFeromoniosH(k, formigas[((int)solucoes[i][0])].getSolucao(j,2))+At-nAt, k, formigas[((int)solucoes[i][0])].getSolucao(j,2));

            }
        }

        // faz a evaporação dos feromonios
        for(int i=0;i<numeroProf;i++){
            for(int j=0;j<numeroTurma;j++){
                int t = (1-p)*Ant::getFeromoniosT(i,j);
                if(t>0)
                    Ant::setFeromoniosT(t,i,j);
                else
                    Ant::setFeromoniosT(0,i,j);

            }
        }

        for(int i=0;i<numeroProf;i++){
            for(int j=0;j<nh;j++){
                int t = (1-p)*Ant::getFeromoniosH(i,j);
                if(t>0)
                    Ant::setFeromoniosH(t,i,j);
                else
                    Ant::setFeromoniosH(0,i,j);
            }
        }



        // copia a melhor solução se ela for melhor que a atual

        Ant::setBestDTF(operacoes::classificaBestHC(formigas[0], prof, disciplina, numeroTurma, numeroProf));
        Ant::setBestSCP(operacoes::classificaBestSC(formigas[0], prof, numeroTurma, numeroProf));

        if(Ant::getBestDTF()>=formigas[solucoes[0].formigas].getDTF()){
            if(Ant::getBestDTF()==formigas[solucoes[0].formigas].getDTF() && Ant::getBestSCP()>formigas[solucoes[0].formigas].getSCP()){
                for(int i=0;i<numeroTurma;i++){
                    Ant::setBestSol(formigas[solucoes[0].formigas].getSolucao(i,0),i, 0);
                    Ant::setBestSol(formigas[solucoes[0].formigas].getSolucao(i,1),i, 1);
                    Ant::setBestSol(formigas[solucoes[0].formigas].getSolucao(i,2),i, 2);
                    Ant::setBestSol(formigas[solucoes[0].formigas].getSolucao(i,3),i, 3);
                    Ant::setBestSol(formigas[solucoes[0].formigas].getSolucao(i,4),i, 4);
                }
            }

            else if(Ant::getBestDTF()>formigas[solucoes[0].formigas].getDTF()){
                for(int i=0;i<numeroTurma;i++){
                    Ant::setBestSol(formigas[solucoes[0].formigas].getSolucao(i,0),i, 0);
                    Ant::setBestSol(formigas[solucoes[0].formigas].getSolucao(i,1),i, 1);
                    Ant::setBestSol(formigas[solucoes[0].formigas].getSolucao(i,2),i, 2);
                    Ant::setBestSol(formigas[solucoes[0].formigas].getSolucao(i,3),i, 3);
                    Ant::setBestSol(formigas[solucoes[0].formigas].getSolucao(i,4),i, 4);

                }
            }


        }

        cout<<"DFT:"<<formigas[solucoes[0].formigas].getDTF();
        cout<<"  SCP:"<<formigas[solucoes[0].formigas].getSCP();
        cout<<"  bestDFT:"<<Ant::getBestDTF();
        cout<<"  bestSCP:"<<Ant::getBestSCP();
        cout<<"  número de stagnações:"<<freeze;
        cout<<"  número de stagnações globais:"<<freeze2;
        cout<<"  número de iterações:"<<iatual<<endl;


        // controla quando a formiga converge
        if(bestDFTAtual > formigas[solucoes[0].formigas].getDTF()){
            bestDFTAtual = formigas[solucoes[0].formigas].getDTF();
        }

        if(bestDFTAtual == formigas[solucoes[0].formigas].getDTF()){ // compara se a melhor solução se repete
            freeze++;
            if(freeze==controlSolFreeze){ // se ela se repete n vezes ele tenta normaliza-las
                double maxFeromoniosT=0; // armazena o maior feromonio das turmas
                double maxFeromoniosH=0; // armazena o maior feromonio dos horarios
                double mediaFeromoniosT=0; // armazena a media de feromonios das turmas
                double mediaFeromoniosH=0; // armazena a media de feromonios das horas

                for(int i=0;i<numeroProf;i++){ // calcula o somatorio dos feromonios e o maior feromonios
                    for(int j=0; j<numeroTurma;j++){
                        mediaFeromoniosT = Ant::getFeromoniosT(i,j) + mediaFeromoniosT;
                        if(maxFeromoniosT < Ant::getFeromoniosT(i,j)){
                            maxFeromoniosT=Ant::getFeromoniosT(i,j);
                        }
                    }


                    for(int j=0; j<nh;j++){
                        mediaFeromoniosH = Ant::getFeromoniosH(i,j) + mediaFeromoniosH;
                        if(maxFeromoniosH < Ant::getFeromoniosH(i,j)){
                            maxFeromoniosH=Ant::getFeromoniosH(i,j);
                        }
                    }

                }
                // faz a media dos feromonios
                mediaFeromoniosT = mediaFeromoniosT/(numeroProf*numeroTurma);
                mediaFeromoniosH = mediaFeromoniosH/(numeroProf*nh);

                for(int i=0;i<numeroProf;i++){ // utiliza a formula para normalizar todos os feromonios
                    for(int j=0; j<numeroTurma;j++){
                        Ant::setFeromoniosT(((Ant::getFeromoniosT(i,j)-mediaFeromoniosT)*((mediaFeromoniosT*w)/maxFeromoniosT)+mediaFeromoniosT), i, j);
                    }


                    for(int j=0; j<nh;j++){
                        Ant::setFeromoniosH(((Ant::getFeromoniosH(i,j)-mediaFeromoniosH)*((mediaFeromoniosH*w)/maxFeromoniosH)+mediaFeromoniosH), i, j);
                    }

                }
                freeze = 0;
                bestDFTAtual = 100000;
            }

        }
        else{ // caso contrario ele reseta o freeze pois as solução nao se repetiu
            freeze = 0;
        }

        if(bestDFTGlobal > Ant::getBestDTF()){
            freeze2 = 0;
            bestDFTGlobal = Ant::getBestDTF();
        }

        if(bestDFTGlobal == Ant::getBestDTF()){ // compara se a melhor solução se repete
            freeze2++;
            if(freeze2==controlBestSolFreeze){ // se ela se repete n vezes ele tenta normaliza-las
                double maxFeromoniosT=0; // armazena o maior feromonio das turmas
                double maxFeromoniosH=0; // armazena o maior feromonio dos horarios
                double mediaFeromoniosT=0; // armazena a media de feromonios das turmas
                double mediaFeromoniosH=0; // armazena a media de feromonios das horas

                for(int i=0;i<numeroProf;i++){ // calcula o somatorio dos feromonios e o maior feromonios
                    for(int j=0; j<numeroTurma;j++){
                        mediaFeromoniosT = Ant::getFeromoniosT(i,j) + mediaFeromoniosT;
                        if(maxFeromoniosT < Ant::getFeromoniosT(i,j)){
                            maxFeromoniosT=Ant::getFeromoniosT(i,j);
                        }
                    }


                    for(int j=0; j<nh;j++){
                        mediaFeromoniosH = Ant::getFeromoniosH(i,j) + mediaFeromoniosH;
                        if(maxFeromoniosH < Ant::getFeromoniosH(i,j)){
                            maxFeromoniosH=Ant::getFeromoniosH(i,j);
                        }
                    }

                }
                // faz a media dos feromonios
                mediaFeromoniosT = mediaFeromoniosT/(numeroProf*numeroTurma);
                mediaFeromoniosH = mediaFeromoniosH/(numeroProf*nh);

                for(int i=0;i<numeroProf;i++){ // utiliza a formula para normalizar todos os feromonios
                    for(int j=0; j<numeroTurma;j++){
                        Ant::setFeromoniosT(((Ant::getFeromoniosT(i,j)-mediaFeromoniosT)*((mediaFeromoniosT*w)/maxFeromoniosT)+mediaFeromoniosT), i, j);
                    }


                    for(int j=0; j<nh;j++){
                        Ant::setFeromoniosH(((Ant::getFeromoniosH(i,j)-mediaFeromoniosH)*((mediaFeromoniosH*w)/maxFeromoniosH)+mediaFeromoniosH), i, j);
                    }

                }
                freeze2 = 0;
                bestDFTGlobal = 100000;
            }

        }

        else{ // caso contrario ele reseta o freeze pois as solução nao se repetiu
            freeze2 = 0;
        }


        iatual++;

    }

    for(int i=0;i<numeroTurma;i++){ // imprime a melhor solução
        cout<<"turma:"<<i;
        for(int j=0;j<4;j++){
            if(j==0)
                cout<<"   Professor:"<<Ant::getBestSol(i,j);
            if(j==1)
                cout<<"   Horario1:"<<Ant::getBestSol(i,j);
            if(j==2)
                cout<<"   Horario2:"<<Ant::getBestSol(i,j);
            if(j==3)
                cout<<"   Disciplina:"<<(disc[Ant::getBestSol(i,j)].codigo)/10<<endl;
        }
    }

    for(int i=0;i<numeroProf;i++){ // marca a quantidade de creditos que o professor possui
        professor[i].SetCreditos(0);
        for(int j=0;j<numeroTurma;j++){
            if(i==Ant::getBestSol(j,0)){
                professor[i].SetCreditos(professor[i].GetCreditos()+ disc[Ant::getBestSol(j,3)].qtdCreditos);
            }
        }
    }

    for(int i=0;i<numeroTurma;i++){ // atualiza o vetor que ira armazenar amelhor soluç~ao
        vector<int> vec(5);
        vec[0] = Ant::getBestSol(i,0);
        vec[1] = Ant::getBestSol(i,1);
        vec[2] = Ant::getBestSol(i,2);
        vec[3] = Ant::getBestSol(i,3);
        vec[4] = Ant::getBestSol(i,4);
        solucaoFinal.push_back(vec);
    }

    formigas[0].getBestSol().clear();

    ofstream arq(resultado);

    arq << Ant::getBestDTF() << ";";
    arq << Ant::getBestSCP() << ";";
    arq << imax <<"\n";

    arq.close();

}

void Principal::gerarSaida(char*end){
    ofstream arq(end);
    arq << "Código;";
    arq << "Tipo;";
    arq << "Nome;";
    arq << "Turma;";
    arq << "Professor;";
    arq << "Créditos;";
    arq << "Horário 1;";
    arq << "Horário 2;";
    arq << "------;";
    arq << "------;";
    arq << "Professores;";
    arq << "Créditos;";
    arq << "Cargo;";
    arq << '\n';

    int numeroTurmas = turmasUtilizadas.size();
    for(int a = 0;a < numeroTurmas;a++)
    {
        switch(turmasUtilizadas[a].disc % 10)
        {
            case 0: arq << "DCC";
                break;
            case 1: arq << "EADDCC";
                break;
            default: cout << "\n\nERRO 12\n\n" << endl;
                exit(12);
        }
        if(turmasUtilizadas[a].disc / 1000 > 0)
            arq << turmasUtilizadas[a].disc / 10 << ';';
        else if(turmasUtilizadas[a].disc / 100 > 0)
            arq << '0' << turmasUtilizadas[a].disc / 10 << ';';
        else
            arq << "00" << turmasUtilizadas[a].disc / 10 << ';';
        switch(disc[turmasUtilizadas[a].indDisc].tipo)
        {
            case 0: arq << "Básica;";
                break;
            case 1: arq << "Massa;";
                break;
            case 2: arq << "Específica;";
                break;
            default: arq << ';';
                cout << "\n\nERRO 10\n\n" << endl;
        }
        arq << disc[turmasUtilizadas[a].indDisc].nome << ';';
        arq << turmasUtilizadas[a].codigo << ';';
        arq << 'P' << Ant::getBestSol(a, 0) << ';';
        arq << disc[turmasUtilizadas[a].indDisc].qtdCreditos << ';';
        switch(Ant::getBestSol(a, 1)/18)
        {
            case 0: arq << "SEG ";
                break;
            case 1: arq << "TER ";
                break;
            case 2: arq << "QUA ";
                break;
            case 3: arq << "QUI ";
                break;
            case 4: arq << "SEX ";
                break;
            default: cout << "\n\nERRO 11\n\n" << endl;
                exit(11);
        }
        arq << (Ant::getBestSol(a, 1)%18)+8 << "h;";

        if(disc[Ant::getBestSol(a,3)].qtdCreditos==4){
            switch(Ant::getBestSol(a, 2)/18)
            {
                case 0: arq << "SEG ";
                    break;
                case 1: arq << "TER ";
                    break;
                case 2: arq << "QUA ";
                    break;
                case 3: arq << "QUI ";
                    break;
                case 4: arq << "SEX ";
                    break;
                default: cout << "\n\nERRO 11\n\n" << endl;
                    exit(11);
            }
            arq << (Ant::getBestSol(a, 2)%18)+8 << "h;";
            arq << ';';
            arq << ';';
        }
        else{
            arq << '-' << ';';
            arq << ';';
            arq << ';';
        }
        if(a < Constantes::getNumeroProf())
        {
            arq << professor[a].GetSiap() << ';';
            arq << professor[a].GetCreditos() << ';';
            arq << professor[a].GetCargo() << ";\n";
        }
        else
            arq << ";\n";

    }
    arq.close();
}

