from tiled import *

class fantasy_maker(Plugin):
    @classmethod
    def nameFilter(cls):
        return "Fantasy Maker custom (*.cus)"

    @classmethod
    def shortName(cls):
        return "fantasy_maker"

    @classmethod
    def write(cls, tileMap, fileName):
        output = ""

        with open(fileName, 'w') as fileHandle:
            if isTileLayerAt(tileMap, 0):
                tileLayer = tileLayerAt(tileMap, 0)
                output += str(tileLayer.height()) + "\n";
                output += str(tileLayer.width()) + "\n";
                for y in range(tileLayer.height()):
                    tiles = []
                    for x in range(tileLayer.width()):
                        if tileLayer.cellAt(x, y).tile() != None:
                            tiles.append(str(tileLayer.cellAt(x, y).tile().id()))
                        else:
                            tiles.append(str(0))
                    line = ','.join(tiles)
                    output += line + '\n'
            if isTileLayerAt(tileMap, 1):
                tileLayer = tileLayerAt(tileMap, 1)
                for y in range(tileLayer.height()):
                    tiles = []
                    for x in range(tileLayer.width()):
                        if tileLayer.cellAt(x, y).tile() != None:
                            tiles.append(str(1))
                        else:
                            tiles.append(str(0))
                    line = ','.join(tiles)
                    output += line + '\n'
            print(output, file=fileHandle)
        return True
