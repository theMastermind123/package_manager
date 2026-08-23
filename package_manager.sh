#!/bin/bash
if ! command -v dpkg-query &> /dev/null; then
    echo "[ERROR] dpkg-query is not installed, are you even debian?"
    exit 1
fi


usage(){
    printf '%s\n' \
    " Usage: ${0} info|install|remove|create|help ARGS" \
    "" \
    " - info: show information of a given package" \
    " - install : install a given package" \
    " - remove: remove a given package" \
    " - create: create a .deb package from a given directory" \
    " - help: show this help"
    local exit_code=$([ ${1} != 1 ] && echo 0 || echo 1)
    exit "${exit_code}"
}

# Number of arguments could be 1 or 2

if [ $# -eq 1 ]; then
    [ "${1}" != "help" ] && usage 1 || usage 0
elif [ $# -ne 2 ]; then
    usage 1
fi

ACTION="${1}"
ARGUMENT="${2}"

# Initiating a table
declare -A ACTIONS=(
    [info]=do_info
    [install]=do_install
    [remove]=do_remove
    [create]=do_create
)


is_pakage_exist(){
    dpkg-query -l "${package}" > /dev/null
}



do_info(){
    local package="${1}"
    if is_pakage_exist "${pakage}"; then
        echo "[DEBUG] Showing info abut pakage: ${package}"
        dpkg-query \
            --show \
            --showformat \
            'pakage:${Package}\nSize:${Installed-Size}\nStatus:${db:Status-Status}\n' \
            "${package}"
    else
        echo "[INFO] package : ${package} is not installed"
    fi
}


do_remove(){
    local package="${1}"
    if is_pakage_exist "${package}"; then  
        echo "[DEBUG] Removing package: ${package}"
        dpkg -P "${package}"
    else   
        echo "[INFO] package: ${package} is already not installed"
    fi
}

do_install(){
    local package="${1}"
    if [[ "${package}" == *.deb ]] && [ ! -f "${package}" ]; then
        echo "[ERROR] Package file ${package} does not exist"
    return
    elif is_package_exist "${package}"; then
        echo "[ERROR] Package ${package} is already installed"
        return
    fi
    echo "[DEBUG] Installing package: ${package}"
    apt install "${package}"
}  

do_create(){
    local directory="${1}"
    echo "[DEBUG] Creating a package for: ${directory}"
    if [ ! -d "${directory}" ]; then
        echo "[ERROR] Directory ${directory} does not exist"
    else
        dpkg-deb -b "${directory}"  
    fi
}



# Running command
do_action(){
    local action="${1}"
    local pakage="${2}"
    local cmd="${ACTIONS[${action}]}"
    [ -z "${cmd}" ] && usage 1
    echo "[DEBUG] Running command : ${cmd}"
    eval "${cmd} ${pakage}"
}


do_action "${ACTION}" "${ARGUMENT}"



