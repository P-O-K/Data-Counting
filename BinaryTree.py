
class Node( object ):
    LEFT, RIGHT = None, None
    def __init__( self, data, parent ):
        self.DATA, self.PARENT = data, parent



class BinaryTree( object ):

    ROOT = None
    TEMPLATES = { 'IN_ORDER': '{left} {center} {right}',
                  'REVERSED': '{right} {center} {left}' }



    def insert( self, data ):
        if not self.ROOT: self.ROOT = Node( data, None )
        else:
            iHelp = self.__insertHandle( self.ROOT, data )
            if data < iHelp.DATA: iHelp.LEFT  = Node( data, iHelp )
            if data > iHelp.DATA: iHelp.RIGHT = Node( data, iHelp )



    def __insertHandle( self, current, data ) -> Node:
        if current.DATA:
            if data < current.DATA:
                if current.LEFT:
                    return self.__insertHandle( current.LEFT, data )
            if data > current.DATA:
                if current.RIGHT:
                    return self.__insertHandle( current.RIGHT, data )
        return current



    def reverseTree( self ):
        self.__reverseTreeHandle( self.ROOT )



    def __reverseTreeHandle( self, location ) -> Node:
        if location:
            locL = self.__reverseTreeHandle( location.LEFT )
            locR = self.__reverseTreeHandle( location.RIGHT )

            location.LEFT, location.RIGHT = locR, locL;
            return location



    def printOrder( self, template='IN_ORDER' ):
        return self.__printOrderHandle( self.ROOT, template )



    def __printOrderHandle( self, current, template ) -> str:
        if current is None: return ''
        left = self.__printOrderHandle( current.LEFT, template )
        data = str( current.DATA )
        right = self.__printOrderHandle( current.RIGHT, template )
        return self.TEMPLATES[template].format( left=left, center=data, right=right )

