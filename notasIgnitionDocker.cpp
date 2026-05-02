Ignition

unlimited number of clients
	web-launcher client
	unlimited tag
	unlimited concurrent designers
bilded in OPC-UA server

Gateway
	primary service, control ignition server
	runs embedded web server
	connects to data
	executes modules
	communicates whth clients
Designer
	web launched application
	configure and build projects
Clients
	launched from the vision client launcher
	found on the gateway webpage
Session
	run in browser
	found on the gateway webpage
--------------------------------------------------------------------------------------------------------------------------------------------------
to limit the amount of RAM memory allowed to docker need to include file .wslconfig in windows user folder
(**********************************)
	# Settings apply across all Linux distros running on WSL 2
	[wsl2]

	# Limits VM memory to use no more than 4 GB, this can be set as whole numbers using GB or MB
	memory=4GB 

	# Sets the VM to use two virtual processors
	processors=2
(**********************************)
--------------------------------------------------------------------------------------------------------------------------------------------------
limit the amount use RAM memory on ignition
	on compose
		environment:
		  - GATEWAY_MAX_MEMORY=2048
		deploy:
		  resources:
			limits:
			  memory: 2.5G
	*** if the backup get some diferent value of the declare in yml run command bellow
		docker exec -it <container_name> sed -i 's/wrapper.java.maxmemory=1024/wrapper.java.maxmemory=2048/' /usr/local/bin/ignition/data/ignition.conf && docker restart <container_name>

	in local
		- open file ignition (./InductiveAutimation/Ignition/data)
		- edit file in:
			# Maximum Java Heap Size (in MB)
			wrapper.java.maxmemory=1024
--------------------------------------------------------------------------------------------------------------------------------------------------
Ignition 8.3 possui o modo "Modes" para pensar em conseito DevOps
	nele podemos criar regras para diferentes modos, por ex.:
		Development Mode
		 - comunica com banco de dados teste como postgresql, mariadb
		Production
		 - comunica com banco de dados do cliente como sqlServer
	Deployment Modes (Modos): O perfil de configuração de rede/banco/segurança (Estou em um ambiente de Teste ou de Produção Real?)

Criado o mode, por ex. Staging, para ativar e preciso acessar o arquivo do linux e alterar
	- local
		acessar a pasta do arquivo ignition.config
			windows -> c:\ProgramFile\InductiveAutimation\Ignition\data
			linux -> /usr/local/bin/ignition/data
		Edite o arquivo, caso linux use o comando
			vmi ignition.config
		em Java Additional Parameters adicione na ultima posicao um novo parametro
			wrapper.java.additional.100=-Dignition.config.mode=Staging
	
	interpretador VS code:
		docker cp ignition-estudo:/usr/local/bin/ignition/data/ignition.conf ./ignition.conf //copia o arquivo ignition,config para pasta local
		docker cp ./ignition.conf ignition-estudo:/usr/local/bin/ignition/data/ignition.conf //substitui o arquivo .config para dento do container
		docker restart ignition-estudo //reinicialize o container
	
	para iniciar o volume com a configuracao altere o yml	
		//alterando volumes deve ter uma copia do arquivo .config para na primeira inicializacao do volume ele substitui o arquivo
		volumes:
			  - ignition-volumes:/usr/local/bin/ignition/data
			  - ./gw-init/ignitionEstudo.gwbk:/restore.gwbk
			  # Adicione esta linha abaixo:
			  - ./ignition.conf:/usr/local/bin/ignition/data/ignition.conf
		//alterando em command ele altera o arquivo .config na inicializacao do volume
		command: >
			  -r /restore.gwbk
			  --
			  wrapper.java.additional.100=-Dignition.config.mode=Staging
--------------------------------------------------------------------------------------------------------------------------------------------------
comands
	cd C:\<ignition path>
	gwcmd.bat -p	//reset password
	gwcmd.bat -r	//restart gateway
--------------------------------------------------------------------------------------------------------------------------------------------------
docker comands
	docker ps -a	//inspect all images
	docker inspect	//provides detailed information on constructs
	docker compose -f docker-compose.yml up -d //Deploy all containers defined in the YAML file
	//pause the container
	docker compose stop //stop
	docker compose stop //run
	//Shuts down the container and deletes the temporary network; container is removed, but volume data is persisted
	docker compose down //stop
	docker compose down -v //stop all containers in compose and remove those volumes
	docker compose down -v --rmi all //stop all containers in compose and remove those volumes end remove all images
	docker compose up -d //run
	docker compose config //diagnoses the file yml
	docker exec <container name> bash -c "./gwcmd.sh -p && ./gwcmd.sh -r" //reset password in docker comand

--------------------------------------------------------------------------------------------------------------------------------------------------
Notas
	para editar arquivos dentro do container copie-o para local edite e substitua
	