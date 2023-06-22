# Metrorec

O código fornecido é uma simulação de uma estação de metrô chamada "METROREC". O programa simula a interação entre passageiros e vagões em uma estação, onde os passageiros esperam pelo vagão e embarcam quando ele chega.

O código principal está contido na função main(). Ele inicia uma estação de metrô usando a função estacao_init() e gera um número aleatório de passageiros. Em seguida, cria uma thread para cada passageiro usando a função pthread_create(). Cada thread de passageiro chama a função passageiros_thread(), onde o passageiro espera pelo vagão usando a função estacao_espera_pelo_vagao() e incrementa um contador atômico chamado counter para rastrear o número de passageiros que estão prontos para embarcar.

Em paralelo, há outra thread chamada vagao_thread() que representa um vagão de metrô. Esta thread é criada em um loop enquanto houver passageiros esperando na estação. A função vagao_thread() preenche o vagão chamando estacao_preencher_vagao(), passando o número de assentos livres no vagão. Dentro de estacao_preencher_vagao(), a função aguarda até que o número de assentos livres seja igual a zero usando pthread_cond_wait().

Uma vez que o vagão está cheio ou não há mais passageiros esperando na estação, a thread do vagão sai do loop e executa o restante do código. Os passageiros são então embarcados um por vez usando a função estacao_embarque() dentro de um loop. Cada vez que um passageiro embarca, o contador atômico counter é decrementado. Se em algum momento o valor do contador atômico counter for maior que o número de passageiros restantes na estação, isso indica um erro.

Após todos os passageiros terem embarcado, o programa imprime uma mensagem indicando que a estação foi finalizada com sucesso.

Além do código principal, há também a definição da estrutura estacao e várias funções auxiliares relacionadas à estação de metrô. Essas funções são responsáveis por inicializar a estação, preencher o vagão, fazer os passageiros esperarem pelo vagão e embarcar nos assentos disponíveis.

Em resumo, o código simula a interação entre passageiros e vagões em uma estação de metrô, garantindo que os passageiros esperem pelo vagão e embarquem corretamente nos assentos disponíveis.
