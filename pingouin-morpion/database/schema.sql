CREATE SCHEMA IF NOT EXISTS jeu;
SET search_path TO jeu;

-- ==========================================
-- 1. NETTOYAGE (Pour repartir propre si besoin)
-- ==========================================
DROP TABLE IF EXISTS possede CASCADE;
DROP TABLE IF EXISTS jouer CASCADE;
DROP TABLE IF EXISTS journal CASCADE;
DROP TABLE IF EXISTS morpion_actif CASCADE;
DROP TABLE IF EXISTS partie CASCADE;
DROP TABLE IF EXISTS config CASCADE;
DROP TABLE IF EXISTS equipe CASCADE;
DROP TABLE IF EXISTS morpion CASCADE;

-- ==========================================
-- 2. TABLES DE RÉFÉRENCE (Statiques)
-- ==========================================

-- Vu dans image_f07bd8.png
CREATE TABLE morpion (
   nom VARCHAR(50),
   image VARCHAR(100),       -- ex: "t1.png"
   point_de_vie INT,         -- ex: 5
   attaque INT,              -- ex: 4
   mana INT,                 -- ex: 2
   reussite DECIMAL(15,2),   -- ex: 60.00
   PRIMARY KEY (nom)
);

-- Vu dans image_f07c38.png
CREATE TABLE equipe (
   couleur VARCHAR(50),      -- ex: "#92F58B"
   nom VARCHAR(50),          -- ex: "bouba11"
   date_creation DATE,       -- ex: 2025-12-03
   PRIMARY KEY (couleur)
);

-- Vu dans image_f07c56.png
CREATE TABLE config (
   id_config VARCHAR(50),          -- ex: "CONF_RAPIDE"
   taille_de_grille INT NOT NULL,  -- ex: 3
   maxtour INT NOT NULL,           -- ex: 10
   date_creation TIMESTAMP DEFAULT CURRENT_TIMESTAMP, -- ex: 2025-12-03T13:15...
   PRIMARY KEY (id_config)
);

-- ==========================================
-- 3. TABLES DE JEU (Dynamiques)
-- ==========================================

-- Vu dans image_f07b9c.png
CREATE TABLE partie (
   idpartie VARCHAR(50),           -- ex: "2320dd7d"
   datedebut TIMESTAMP NOT NULL,
   datefin TIMESTAMP,              -- NULL au début
   gagnant VARCHAR(50),            -- NULL au début
   id_config VARCHAR(50),          -- Lien vers la config
   PRIMARY KEY (idpartie),
   FOREIGN KEY (id_config) REFERENCES config(id_config)
);

-- Vu dans image_f07c17.png
CREATE TABLE jouer (
   couleur VARCHAR(50),
   idpartie VARCHAR(50),
   PRIMARY KEY (couleur, idpartie),
   FOREIGN KEY (couleur) REFERENCES equipe(couleur),
   FOREIGN KEY (idpartie) REFERENCES partie(idpartie)
);

-- Vu dans image_f07b80.png
CREATE TABLE possede (
   nom VARCHAR(50),        -- Le morpion
   couleur VARCHAR(50),    -- L'équipe
   PRIMARY KEY (nom, couleur),
   FOREIGN KEY (nom) REFERENCES morpion(nom),
   FOREIGN KEY (couleur) REFERENCES equipe(couleur)
);

-- Vu dans image_f07bf6.png
CREATE TABLE journal (
   numligne SERIAL,        -- 1, 2, 3... (Auto-incrément)
   date_ TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
   action VARCHAR(100),    -- ex: "PLACE:0:0:Bleu"
   idpartie VARCHAR(50) NOT NULL,
   PRIMARY KEY (numligne),
   FOREIGN KEY (idpartie) REFERENCES partie(idpartie)
);

-- Vu dans image_f07bb9.png (Vide mais présente)
-- Structure nécessaire pour la partie avancée
CREATE TABLE morpion_actif (
    idpartie VARCHAR(50),
    x INT, 
    y INT,
    couleur VARCHAR(50),
    nom_morpion VARCHAR(50),
    pv_actuel INT DEFAULT 0,
    mana_actuel INT DEFAULT 0,
    attaque INT DEFAULT 0,
    reussite DECIMAL(15,2) DEFAULT 0,
    
    PRIMARY KEY (idpartie, x, y),
    FOREIGN KEY (idpartie) REFERENCES partie(idpartie),
    FOREIGN KEY (couleur) REFERENCES equipe(couleur),
    FOREIGN KEY (nom_morpion) REFERENCES morpion(nom)
);