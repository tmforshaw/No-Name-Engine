#include "Chunk.hpp"

#include "../Renderer/Renderer.hpp"
#include "World.hpp"

Chunk::Chunk() : m_posX( 0 ), m_posY( 0 ), m_posZ( 0 ) {}

Chunk::Chunk( const unsigned short& p_posX, const unsigned short& p_posY, const unsigned short& p_posZ )
	: m_posX( p_posX ), m_posY( p_posY ), m_posZ( p_posZ )
{
	for ( unsigned short y = 0; y < CHUNK_SIZE; y++ )		  // Iterate Y
		for ( unsigned short z = 0; z < CHUNK_SIZE; z++ )	  // Iterate Z
			for ( unsigned short x = 0; x < CHUNK_SIZE; x++ ) // Iterate X
			{
				m_cubes[y][z][x] = 1;
			}

	GenerateMesh();
}

unsigned short Chunk::GetNeighbourChunkBlock( const unsigned short& x, const unsigned short& y, const unsigned short& z, const Face& face ) const
{
	unsigned short new_x = x, new_y = y, new_z = z;
	unsigned short chunk_x = m_posX, chunk_y = m_posY, chunk_z = m_posZ;

	switch ( face )
	{
	case Face::FRONT:
		new_z = CHUNK_SIZE - 1;

		if ( m_posZ > 0 )
			chunk_z--;
		else
			return 0; // Return 0 because this is the last chunk
		break;

	case Face::BACK:
		new_z = 0;

		if ( m_posZ < CHUNKS_Z - 1 )
			chunk_z++;
		else
			return 0; // Return 0 because this is the last chunk
		break;

	case Face::RIGHT:
		new_x = CHUNK_SIZE - 1;

		if ( m_posX > 0 )
			chunk_x--;
		else
			return 0; // Return 0 because this is the last chunk
		break;

	case Face::LEFT:
		new_x = 0;

		if ( m_posX < CHUNKS_X - 1 )
			chunk_x++;
		else
			return 0; // Return 0 because this is the last chunk
		break;

	case Face::BOTTOM:
		new_y = CHUNK_SIZE - 1;

		if ( m_posY > 0 )
			chunk_y--;
		else
			return 0; // Return 0 because this is the last chunk
		break;

	case Face::TOP:
		new_y = 0;

		if ( m_posY < CHUNKS_Y - 1 )
			chunk_y++;
		else
			return 0; // Return 0 because this is the last chunk
		break;

	default:
		// You should never reach here
		break;
	}

	return World::GetChunk( chunk_x, chunk_y, chunk_z ).GetCube( new_x, new_y, new_z );
}

unsigned short Chunk::GetNeighbour( const unsigned short& x, const unsigned short& y, const unsigned short& z, const Face& face ) const
{
	unsigned short new_x = x, new_y = y, new_z = z;

	switch ( face )
	{
	case Face::FRONT:
		if ( z > 0 ) new_z--;
		else
			goto outsideChunk;
		break;

	case Face::BACK:
		if ( z < CHUNK_SIZE - 1 ) new_z++;
		else
			goto outsideChunk;
		break;

	case Face::LEFT:
		if ( x > 0 ) new_x--;
		else
			goto outsideChunk;
		break;

	case Face::RIGHT:
		if ( x < CHUNK_SIZE - 1 ) new_x++;
		else
			goto outsideChunk;
		break;

	case Face::BOTTOM:
		if ( y > 0 ) new_y--;
		else
			goto outsideChunk;
		break;

	case Face::TOP:
		if ( y < CHUNK_SIZE - 1 ) new_y++;
		else
			goto outsideChunk;
		break;

	default:
		// You should never reach here
		break;
	}

	return m_cubes[new_y][new_z][new_x];

outsideChunk:

	return GetNeighbourChunkBlock( x, y, z, face ); // Index is outside of chunk, check the neighbouring chunk
}

void Chunk::GenerateMesh()
{
	// Reset the mesh and indices
	m_mesh	  = {};
	m_indices = {};

	unsigned short total = 0;

	// Add the cube faces depending on neighbours
	for ( unsigned short y = 0; y < CHUNK_SIZE; y++ )		  // Iterate Y
		for ( unsigned short z = 0; z < CHUNK_SIZE; z++ )	  // Iterate Z
			for ( unsigned short x = 0; x < CHUNK_SIZE; x++ ) // Iterate X
			{
				if ( m_cubes[y][z][x] > 0 )						  // Is a block
					for ( auto& face : faceItr )				  // Iterate through Face enum
						if ( GetNeighbour( x, y, z, face ) == 0 ) // Neighbour isn't a block
							Cube::PushFaceWithMatrix( &m_mesh, &m_indices, m_cubes[y][z][x], face, glm::translate( glm::mat4( 1.0f ), GetPosition( x, y, z ) ) );
			}

	// // Set the buffers
	// m_vertexBuffer.SetData( m_mesh.data(), m_mesh.size() * sizeof( Vertex ) );
	// m_indexBuffer.SetData( m_indices.data(), m_indices.size() );
}

void Chunk::DrawMesh( const VertexArray& p_VAO, const ShaderProgram& shader ) const
{
	// p_VAO.Bind();
	// m_vertexBuffer.Bind();

	// Renderer::Draw( p_VAO, m_indexBuffer, shader );
}

void Chunk::PushVertices( std::vector<Vertex>* p_vertices, std::vector<unsigned int>* p_indices )
{
	// GenerateMesh();

	for ( const auto& vert : m_mesh ) // Iterate each vertex of the mesh
		p_vertices->push_back( vert );

	// std::cout << "Vertices: " << p_vertices->size() / 4 << std::endl;

	for ( const auto& index : m_indices ) // Iterate each index of the indices
		p_indices->push_back( index );

	// std::cout << "Indices: " << p_indices->size() / 6 << std::endl;
}