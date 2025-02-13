# Out of Combat Mana Regen Module

Simple module that grants out of combat players increased mana regen.

## Standard Installation
Clone to modules directory:
```bash
cd path/to/azerothcore/modules
git clone https://github.com/StevenDankMeister/mod-ooc-mana-regen
```
Re-run cmake and launch a clean build of AzerothCore.

## Docker Installation
```bash
cd path/to/azerothcore/modules
git clone git@github.com:StevenDankMeister/mod-ooc-mana-regen.git
cd ..
docker compose up -d --build
```

## Module Configuration

### Standard
TODO
### Docker
Edit the `OOCManaRegen.conf.dist` file inside `mod-ooc-mana-regen/conf`.

(If previously built) Delete `OOCManaRegen.conf.dist` inside `path/to/azerothcore/env/dist/etc/modules`.

Rebuild and restart the server:
```bash
docker compose up -d --build
```
