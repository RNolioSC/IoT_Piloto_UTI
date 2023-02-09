DROP TABLE IF EXISTS PacienteDiagnostico;
DROP TABLE IF EXISTS Pacientes;
DROP TABLE IF EXISTS Diagnosticos;
DROP TABLE IF EXISTS AtendimentoEnfermeiro;
DROP TABLE IF EXISTS Enfermeiros;
DROP TABLE IF EXISTS AtendimentoTecnicoEnf;
DROP TABLE IF EXISTS TecnicosEnf;
DROP TABLE IF EXISTS Atendimentos;
DROP TABLE IF EXISTS AtividadesNAS;

CREATE TABLE Pacientes (codigo SERIAL PRIMARY KEY, nome VARCHAR(50)); 

CREATE TABLE Diagnosticos(codigo SERIAL PRIMARY KEY, nome VARCHAR(50));

CREATE TABLE PacienteDiagnostico(
	codPaciente int,
	codDiagnostico int,
	PRIMARY KEY(codPaciente, codDiagnostico),
	CONSTRAINT fk1 FOREIGN KEY (codPaciente) REFERENCES Pacientes(codigo) ,
	CONSTRAINT fk2 FOREIGN KEY (codDiagnostico) REFERENCES Diagnosticos(codigo)
);

CREATE TABLE AtividadesNAS(codigoNAS VARCHAR(2) PRIMARY KEY, descricao VARCHAR(50));


CREATE TABLE Atendimentos (codigo SERIAL PRIMARY KEY, diaHora TIMESTAMP, 
						   atividade VARCHAR(2),
						   paciente int,
						   FOREIGN KEY (atividade) REFERENCES AtividadesNAS(codigoNAS),
						   FOREIGN KEY (paciente) REFERENCES Pacientes(codigo)
						   );


CREATE TABLE Enfermeiros (codigo VARCHAR(8) PRIMARY KEY, nome VARCHAR(50));

CREATE TABLE AtendimentoEnfermeiro(
	codAtendimento int,
	codEnfermeiro VARCHAR(8),
	PRIMARY KEY (codAtendimento, codEnfermeiro),
	FOREIGN KEY (codAtendimento) REFERENCES Atendimentos(codigo),
	FOREIGN KEY (codEnfermeiro) REFERENCES Enfermeiros(codigo)
);

CREATE TABLE TecnicosEnf (codigo VARCHAR(8) PRIMARY KEY, nome VARCHAR(50));


CREATE TABLE AtendimentoTecnicoEnf(
	codAtendimento int,
	codTecnicoEnf VARCHAR(8),
	PRIMARY KEY (codAtendimento, codTecnicoEnf),
	FOREIGN KEY (codAtendimento) REFERENCES Atendimentos(codigo),
	FOREIGN KEY (codTecnicoEnf) REFERENCES TecnicosEnf(codigo)
);