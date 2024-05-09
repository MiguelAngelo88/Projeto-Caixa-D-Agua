**Monitoramento do nível da Caixa D'Água com alarme**
Funcionamento:
- 3 sensores de nível estão dispostos na caixa d'água em alturas que representam aproximadamente 100%, 50% e 25% de água presente na caixa.
- Para cada sensor existe um respectivo led que irá acender quando o sensor estiver identificando água.
- Quando os 3 sensores estiverem identificando água(caixa cheia), um buzzer irá começar a tocar por um intervalo de 10 segundos(toca 10 segundos, aguarda 10 segundos, etc), ao menos
  que o botão seja pressinado, mutando o buzzer.
- O mesmo se repete para quando os 3 sensores não estiverem identificando água(caixa vazia).

Configuração do hardware:
- sensor 100% na porta digital 2
- sensor 50% na porta digital 3
- sensor 25% na porta digital 4
- Led 100% na porta digital 6
- Led 50% na porta digital 7
- Led 25% na porta digital 8
- buzzer na porta digital 9
- botão para mutar o buzzer na porta digital 10

Dimensionamento:
Altura da caixa = 73 cm
- Nível 1 = 15 cm
- Nível 2 = 36,5 cm
- Nível 3 = 68 cm
