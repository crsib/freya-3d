#include "freya/FreyaRenderTarget.h"
#include "freya/FreyaGeometryBuffer.h"

namespace CEGUI
{
namespace freya
{
FreyaRenderTarget::FreyaRenderTarget()
:m_Viewport(0,0,0,0)
{
	m_Rapi = core::EngineCore::getRenderingDriver();
	m_MatrixValid = false;
}

const Rect &
FreyaRenderTarget::getArea() const
{
	return m_Viewport;
}

FreyaRenderTarget::~FreyaRenderTarget()
{

}

void FreyaRenderTarget::draw(const GeometryBuffer & buffer)
{
	buffer.draw();
}

void FreyaRenderTarget::deactivate()
{
	m_Rapi->setViewport(m_Vp[0],m_Vp[1],m_Vp[2],m_Vp[3]);
}

void FreyaRenderTarget::setArea(const Rect & area)
{
	m_Viewport = area;
	m_MatrixValid = false;
}

void FreyaRenderTarget::activate()
{
	if(!m_MatrixValid)
		updateMatrix();
	m_Vp = m_Rapi->getViewport();

	m_Rapi->setViewport(m_Viewport.d_left,m_Viewport.d_top,m_Viewport.d_right,m_Viewport.d_bottom);
	m_Rapi->setMatrix(renderer::Matrix::PROJECTION,m_Matrix);

	m_Rapi->setMatrix(renderer::Matrix::VIEW,math::matrix4x4::identity);

}

void FreyaRenderTarget::draw(const RenderQueue & queue)
{
	queue.draw();
}

void
FreyaRenderTarget::unprojectPoint(const GeometryBuffer & buff, const Vector2 & p_in, Vector2 & p_out) const
{
	if(!m_MatrixValid)
		updateMatrix();
	const FreyaGeometryBuffer& gb = static_cast<const FreyaGeometryBuffer&>(buff);

	const float midx = m_Viewport.getWidth() * 0.5f;
	const float midy = m_Viewport.getHeight() * 0.5f;

	const math::matrix4x4 vpmat(
			midx,    0,    0,    m_Viewport.d_left + midx,
			0,    -midy,  0,    m_Viewport.d_top + midy,
			0,      0,    1,    0,
			0,      0,    0,    1
	);

	const math::matrix4x4 proj (gb.getTransformation()*m_Matrix*vpmat);
	const math::matrix4x4 unproj(math::inversed(proj));

	math::vector3d in;

	in.x = midx;
	in.y = midy;
	in.z = - m_ViewDistance;

	const math::vector3d r1(unproj * in);
	in.x = p_in.d_x;
	in.y = p_in.d_y;
	in.z = 0;
	// calculate vector of picking ray
	const math::vector3d rv(r1 - unproj * in);

	// project points to orientate them with GeometryBuffer plane
	in.x = 0.0;
	in.y = 0.0;
	const math::vector3d p1(proj * in);
	in.x = 1.0;
	in.y = 0.0;
	const math::vector3d p2(proj * in);
	in.x = 0.0;
	in.y = 1.0;
	const math::vector3d p3(proj * in);

	// calculate the plane normal
	const math::vector3d pn((p2 - p1)*(p3 - p1));
	// calculate distance from origin
	const float plen = math::abs(pn);
	const float dist = -(p1.x * (pn.x / plen) +
			p1.y * (pn.y / plen) +
			p1.z * (pn.z / plen));

	// calculate intersection of ray and plane
	const float pn_dot_rv = (pn,rv);
	const float tmp = pn_dot_rv != 0.0 ?
			((pn,r1) + dist) / pn_dot_rv :
	0.0;

	p_out.d_x = static_cast<float>(r1.x - rv.x * tmp);
	p_out.d_y = static_cast<float>(r1.y - rv.y * tmp);


}

void
FreyaRenderTarget::updateMatrix() const
{
	m_MatrixValid = true;
	const float w = m_Viewport.getWidth();
	const float h = m_Viewport.getHeight();

	const float aspect = w / h;
	const float midx = w * 0.5;
	const float midy = h * 0.5;
	m_ViewDistance = midx / (aspect * 0.267949192431123);

	const float nearZ = m_ViewDistance * 0.5f;
	const float farZ = m_ViewDistance * 2.0f;
	const float nr_sub_far = nearZ - farZ;

	math::matrix4x4	mtx;

	mtx.elem[0][0] = 3.732050808f / aspect;
	mtx.elem[0][3] = -m_ViewDistance;
	mtx.elem[1][1] = -3.732050808f;
	mtx.elem[1][3] = m_ViewDistance;
	mtx.elem[2][2] = -((farZ + nearZ) / nr_sub_far);
	mtx.elem[3][2] = 1.0f;
	mtx.elem[3][3] = m_ViewDistance;

	m_Matrix = mtx;
}

}
}
