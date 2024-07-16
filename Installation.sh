#!/bin/bash

REPO_URL="git@github.com:Krio18/RayTracer.git"
INSTALL_DIR="RayTracer"

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

error_exit() {
    echo -e "${RED}[ERREUR] $1${NC}" 1>&2
    exit 1
}

success() {
    echo -e "${GREEN}[SUCCÈS] $1${NC}"
}

install_prerequisites() {
    local packages=("git" "g++" "make" "libconfig++-dev")

    for pkg in "${packages[@]}"; do
        if ! dpkg -s $pkg > /dev/null 2>&1; then
            echo "Installation de $pkg..."
            sudo apt-get install -y $pkg || error_exit "Impossible d'installer $pkg."
        else
            success "$pkg est déjà installé."
        fi
    done
}

clone_repo() {
    if [ -d "$INSTALL_DIR" ]; then
        echo "Le répertoire $INSTALL_DIR existe déjà. Suppression en cours..."
        rm -rf $INSTALL_DIR || error_exit "Impossible de supprimer le répertoire $INSTALL_DIR."
    fi

    git clone $REPO_URL $INSTALL_DIR || error_exit "Impossible de cloner le dépôt."
    success "Dépôt cloné avec succès dans $INSTALL_DIR."
}

build_project() {
    cd $INSTALL_DIR || error_exit "Impossible d'accéder au répertoire $INSTALL_DIR."
    make || error_exit "La construction du projet a échoué."
    success "Projet construit avec succès."
}

update_repo() {
    if [ -d "$INSTALL_DIR" ]; then
        cd $INSTALL_DIR || error_exit "Impossible d'accéder au répertoire $INSTALL_DIR."
        git pull || error_exit "Impossible de mettre à jour le dépôt."
        success "Dépôt mis à jour avec succès."
        build_project
    else
        error_exit "Le répertoire $INSTALL_DIR n'existe pas. Veuillez cloner le dépôt d'abord."
    fi
}

delete_project() {
    if [ -d "$INSTALL_DIR" ]; then
        rm -rf $INSTALL_DIR || error_exit "Impossible de supprimer le répertoire $INSTALL_DIR."
        success "Projet supprimé avec succès."
    else
        error_exit "Le répertoire $INSTALL_DIR n'existe pas."
    fi
}

show_help() {
    echo "Usage: $0 [OPTION]"
    echo
    echo "Options:"
    echo "  --install   Installe le projet"
    echo "  --update    Met à jour le projet"
    echo "  --delete    Supprime le projet"
    echo "  -h, --help  Affiche cette aide"
}

if [[ $# -eq 0 ]]; then
    show_help
    exit 1
fi

case "$1" in
    --install
        install_prerequisites
        clone_repo
        build_project
        success "Installation et configuration terminées avec succès."
        ;;
    --update
        update_repo
        ;;
    --delete
        delete_project
        ;;
    -h|--help
        show_help
        ;;
    *
        echo "Option inconnue: $1"
        show_help
        exit 1
        ;;
esac
