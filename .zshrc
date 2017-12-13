# Executes commands at the start of an interactive session.
#
# Authors:
#   Sorin Ionescu <sorin.ionescu@gmail.com>
#

# Source Prezto.
if [[ -s "${ZDOTDIR:-$HOME}/.zprezto/init.zsh" ]]; then
  source "${ZDOTDIR:-$HOME}/.zprezto/init.zsh"
fi

export PATH=$PATH:/sbin:/usr/sbin

# Customize to your needs...
# export TERM=xterm-256color
export PAGER=less
export EDITOR="vim"
export VISUAL="vim"
export BROWSER="firefox"
export RANGER_LOAD_DEFAULT_RC=FALSE
export LANG=en_US.UTF-8
export PATH="${PATH}:${HOME}/.local/bin/"

# home and key to work
bindkey '\e[1~' beginning-of-line
bindkey '\e[4~' end-of-line
export KEYTIMEOUT=1
bindkey '^P' up-history
bindkey '^N' down-history
bindkey '^?' backward-delete-char
bindkey '^h' backward-delete-char
bindkey '^r' history-incremental-search-backward
bindkey -M vicmd 'k' history-substring-search-up
bindkey -M vicmd 'j' history-substring-search-down

zle -N zle-line-init
zle -N zle-keymap-select
zstyle ":completion:*" rehash true
setopt COMPLETE_ALIASES

# custom command

alias xbps-install='sudo xbps-install'
alias xbps-reconfigure='sudo xbps-reconfigure'
alias -s mpv='mpv --loop=8'
alias -s webm='mpv --loop=8'
alias rm='rm -I'
alias mkdir='mkdir -p -v'
alias grep='grep --color=auto'
alias du='du -c -h'
alias svim='sudo vim'
alias pacman='sudo pacman'
alias sxiv='sxiv -b'
alias neofetch='neofetch --w3m ~/Imagens/neofetch.png'
alias tmux='tmux -2'

alias ls='ls --group-directories-first --time-style=+"%d.%m.%Y %H:%M" --color=auto -F'
alias ll='ls --group-directories-first --time-style=+"%d.%m.%Y %H:%M" --color=auto -F'
alias la='ls -lha --group-directories-first --time-style=+"%d.%m.%Y %H:%M" --color=auto -F'

alias :q='exit'
alias :x='exit'
alias trans='trans :vi'
alias rsync='rsync -avzhe --progress'
#############################
setsid wal -r

##############################
if which ruby >/dev/null && which gem >/dev/null; then
    PATH="$(ruby -rubygems -e 'puts Gem.user_dir')/bin:$PATH"
fi
##############################
export FSTART="/home/xmiah/tmpfs"

if [[ $PWD == $HOME ]]; then
  cd $FSTART
fi
