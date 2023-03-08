CREATE DATABASE "BancoDeDados"
    WITH
    OWNER = postgres
    ENCODING = 'UTF8'
    CONNECTION LIMIT = -1
    IS_TEMPLATE = False;

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

CREATE TABLE AtividadesNAS(codigoNAS VARCHAR(2) PRIMARY KEY, descricao VARCHAR(500), pontos float);


CREATE TABLE Atendimentos (codigo SERIAL PRIMARY KEY, diaHora TIMESTAMP, 
						   atividade VARCHAR(2),
						   paciente int,
						   FOREIGN KEY (atividade) REFERENCES AtividadesNAS(codigoNAS),
						   FOREIGN KEY (paciente) REFERENCES Pacientes(codigo)
						   );


CREATE TABLE profissionaisEnf (codigo VARCHAR(8) PRIMARY KEY, nome VARCHAR(50), tipo char);

CREATE TABLE AtendimentoProfEnf(
	codAtendimento int,
	codProfEnf VARCHAR(8),
	PRIMARY KEY (codAtendimento, codProfEnf),
	FOREIGN KEY (codAtendimento) REFERENCES Atendimentos(codigo),
	FOREIGN KEY (codProfEnf) REFERENCES profissionaisEnf(codigo)
);