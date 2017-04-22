#include "Lampada.h" //include the declaration for this class

//<<constructor>> 
Lampada::Lampada(int pino){
    pinMode(pino, OUTPUT); // configura o pino como saida. 
    Pino = pino;
    p_cnt = l_cnt = 0; // Nenhum PIR e LDR adicionados
}

//<<destructor>>
Lampada::~Lampada(){/*nothing to destruct*/}

// Verifica se pode acender a lampada. Depende se tiver PIR e LDR associado a lampada. 
void Lampada::verifica(){
// depuracao    
    
    // contadores que verifica se pir e o led está ligado
    int cont_pir = 0;
    int cont_led = 0;
	// se tiver algum PIR ative-o
	Serial.println("PIRs");
	for (int i=0; i < p_cnt; i++){
	    Serial.println(pirs[i]);
	    int pino = pirs[i];
	    Serial.print(" PIR "); Serial.print(pino);
	    Serial.print("= "); Serial.println(digitalRead(pino));
		
		// verifica se o pir está ativo
		if(digitalRead(pino))
		    cont_pir++;
	}
    
    //int noite = 1;
	// se tiver algum LDR, acende todos os ativos
    Serial.println("LDRs");
	for (int i=0; i < l_cnt; i++){
        Serial.println(ldrs[i]);
        int pino = pirs[i];
        Serial.print(" LDR "); Serial.print(pino);
        Serial.print("= "); Serial.println(analogRead(pino));
      
        // verifica se o pir está ativo
		if(analogRead(pino))
	        cont_led++;
        
    }
    
    //if(noite) digitalWrite(pino,HIGH);
    //else digitalWrite(pino,LOW);

// inserir seu codigo para acender Se todos LDR estiverem ativos e pelo menos 1 PIR.
    if(cont_led == l_cnt && cont_pir > 0){
        for (int i=0; i < p_cnt; i++){
	        int pino = pirs[i];
	        digitalWrite(pino,HIGH);
	    }
	    for (int i=0; i < l_cnt; i++){
            int pino = pirs[i];
            digitalWrite(pino,HIGH);
        }
    } else if(cont_led == l_cnt){ // Caso tenha somente PIR, ativa se um ou mais estiverem ativos.
        for (int i=0; i < l_cnt; i++){
            int pino = pirs[i];
            digitalWrite(pino,HIGH);
        }
    } else if(cont_pir > 0){ // Caso tenha somente LDR, acende se todos estiverem ativos
        for (int i=0; i < p_cnt; i++){
	        int pino = pirs[i];
	        digitalWrite(pino,HIGH);
	    }
    } 
    // Caso não tenha PIR nem LDR não faz nada

}


// Adiciona um PIR sensor de Presenca, a lampada acende se pelo menos um PIR estiver ligado.
void Lampada::PIR(int pino){
  pinMode(pino, INPUT); // configura o pino como entrada. 
  if ( p_cnt < _MAX_S ) {
    pirs[p_cnt] = pino;
    p_cnt++;
    Serial.print("PIR pino="); Serial.println(pino); 
  }
 
}	

// Adiciona um LDR, a lampada acende se todos os LDRS estiverem ligados.
void Lampada::LDR(int pino){
  pinMode(pino, INPUT); // configura o pino como entrada. 
 if ( l_cnt < _MAX_S ) {
    ldrs[l_cnt] = pino;
    l_cnt++;
    Serial.print("LDR pino="); Serial.println(pino); 
  }
 
}	

