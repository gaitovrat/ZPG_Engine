#include "AbstractLight.hpp"

#include "Observer/IObserver.hpp"

uint64_t AbstractLight::m_lastId = 0;

AbstractLight::AbstractLight() : AbstractLight(glm::vec3(), 1.f, .0f, .0f, glm::vec3(), glm::vec3(), glm::vec3())
{
}

AbstractLight::AbstractLight(const glm::vec3& position, const float constant, const float linear, const float quadratic, const glm::vec3& ambient,
	const glm::vec3& diffuse, const glm::vec3& specular): m_position(position),
	                                                      m_constant(constant),
	                                                      m_linear(linear),
	                                                      m_quadratic(quadratic),
	                                                      m_ambient(ambient),
	                                                      m_diffuse(diffuse),
	                                                      m_specular(specular),
	                                                      m_id(m_lastId++)
{
}

AbstractLight::AbstractLight(AbstractLight&& other) noexcept:
	m_observers(std::move(other.m_observers)),
	m_position(other.m_position),
	m_constant(other.m_constant),
	m_linear(other.m_linear),
	m_quadratic(other.m_quadratic),
	m_ambient(other.m_ambient),
	m_diffuse(other.m_diffuse),
	m_specular(other.m_specular),
	m_id(other.m_id)
{
}

AbstractLight& AbstractLight::operator=(const AbstractLight& other)
{
	if (this == &other)
		return *this;

	m_observers = other.m_observers;
	m_position = other.m_position;
	m_constant = other.m_constant;
	m_linear = other.m_linear;
	m_quadratic = other.m_quadratic;
	m_ambient = other.m_ambient;
	m_diffuse = other.m_diffuse;
	m_specular = other.m_specular;
	m_id = other.m_id;

	return *this;
}

AbstractLight& AbstractLight::operator=(AbstractLight&& other) noexcept
{
	if (this == &other)
		return *this;

	m_observers = std::move(other.m_observers);
	m_position = other.m_position;
	m_constant = other.m_constant;
	m_linear = other.m_linear;
	m_quadratic = other.m_quadratic;
	m_ambient = other.m_ambient;
	m_diffuse = other.m_diffuse;
	m_specular = other.m_specular;
	m_id = other.m_id;

	return *this;
}

glm::vec3 AbstractLight::Position() const
{
	return m_position;
}

void AbstractLight::SetPosition(const glm::vec3 position)
{
	m_position = position;
}

float AbstractLight::Constant() const
{
	return m_constant;
}

void AbstractLight::SetConstant(const float constant)
{
	m_constant = constant;
}

float AbstractLight::Linear() const
{
	return m_linear;
}

void AbstractLight::SetLinear(const float linear)
{
	m_linear = linear;
}

float AbstractLight::Quadratic() const
{
	return m_quadratic;
}

void AbstractLight::SetQuadratic(const float quadratic)
{
	m_quadratic = quadratic;
}

glm::vec3 AbstractLight::Ambient() const
{
	return m_ambient;
}

void AbstractLight::SetAmbient(const glm::vec3 ambient)
{
	m_ambient = ambient;
}

glm::vec3 AbstractLight::Diffuse() const
{
	return m_diffuse;
}

void AbstractLight::SetDiffuse(const glm::vec3 diffuse)
{
	m_diffuse = diffuse;
}

glm::vec3 AbstractLight::Specular() const
{
	return m_specular;
}

void AbstractLight::SetSpecular(const glm::vec3 specular)
{
	m_specular = specular;
}

uint64_t AbstractLight::Id() const
{
    return m_id;
}

void AbstractLight::AddObserver(IObserver* observer)
{
    for (const auto& element : m_observers)
    {
        if (element == observer)
        {
            return;
        }
    }

    m_observers.push_back(observer);
}

void AbstractLight::NotifyAll(const EObserverEvent event)
{
    for (const auto& element : m_observers)
    {
        element->Notify(event, this);
    }
}