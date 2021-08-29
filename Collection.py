
class Node( object ):
	"""docstring for Node"""
	LEFT, RIGHT = None, None
	def __init__( self, data, parent ):
		super( Node, self ).__init__( )
		self.DATA, self.PARENT, self.COUNT = data, parent, 1



class DataCollection( object ):
	"""docstring for DataCollection"""

	ROOT = None


	def include( self, instance ) -> None:
		if not self.ROOT: self.ROOT = Node( instance, None )
		else:
			local = self.__includeHandle( self.ROOT, instance )
			if instance < local.DATA: local.LEFT  = Node( instance, local )
			if instance > local.DATA: local.RIGHT = Node( instance, local )
			if instance == local.DATA: local.COUNT += 1



	def __includeHandle( self, current:Node, data ) -> Node:
		if current.DATA:
			if data < current.DATA:
				if current.LEFT:
					return self.__includeHandle( current.LEFT, data )
			if data > current.DATA:
				if current.RIGHT:
					return self.__includeHandle( current.RIGHT, data )
		return current



	def find( self, data ) -> Node:
		return self.__includeHandle( self.ROOT, data )



	def empty( self ) -> None:
		self.ROOT = None



	def count( self, string:str, words:bool=False ) -> dict:
		if words: string = string.split( ' ' )
		for instance in string:
			self.include( instance )
		return self.__getCollectionHandle( self.ROOT, {} )



	def reverseTree( self ) -> None:
		self.__reverseTreeHandle( self.ROOT )



	def __reverseTreeHandle( self, location:Node ) -> Node:
		if location:
			loc_L = self.__reverseTreeHandle( location.LEFT )
			loc_R = self.__reverseTreeHandle( location.RIGHT )

			location.LEFT, location.RIGHT = loc_R, loc_L;
			return location



	def getCollection( self ) -> dict:
		return self.__getCollectionHandle( self.ROOT, {} )



	def __getCollectionHandle( self, nodeLocation:Node, dictionary:dict ) -> dict:
		if nodeLocation is None: return ''
		self.__getCollectionHandle( nodeLocation.LEFT, dictionary )
		dictionary[ str( nodeLocation.DATA ) ] = nodeLocation.COUNT
		self.__getCollectionHandle( nodeLocation.RIGHT, dictionary )
		return dictionary



if __name__ == '__main__':
	CLT = DataCollection( )
	print( CLT.count( 'the quick brown fox jumps over the lazy dog', words=True ) )
	print( '"the" occures {} times in the sentence!!'.format( CLT.find( 'the' ).COUNT ) )
