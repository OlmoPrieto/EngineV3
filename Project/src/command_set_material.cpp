#include "command_set_material.h"

CommandSetMaterial::CommandSetMaterial(std::shared_ptr<MaterialInstance> _spMaterial)
  : m_spMaterial(_spMaterial)
{

}

CommandSetMaterial::~CommandSetMaterial()
{

}

void CommandSetMaterial::execute()
{
  const std::shared_ptr<Material>& spMaterial = m_spMaterial->getReferenceMaterial();

  if (m_spMaterial->checkReady() == true)
  {
    Program& oProgram = spMaterial->getProgram();
    //if (sm_oOpenGL.getProgramInUse() != oProgram.getInternalId())
      sm_oOpenGL.useProgram(oProgram);

    for (std::unique_ptr<Attribute>& pAttribute : m_spMaterial->getAttributes())
    {
      ValueType eType = pAttribute->getType();
      switch (eType)
      {
        case ValueType::Float:
        {
          sm_oOpenGL.setUniformValue(sm_oOpenGL.getUniformLocation(oProgram, pAttribute->getName().c_str()),
            eType, &pAttribute->getData<float>());

          break;
        }
        case ValueType::Uint:
        {
          sm_oOpenGL.setUniformValue(sm_oOpenGL.getUniformLocation(oProgram, pAttribute->getName().c_str()),
            eType, &pAttribute->getData<uint32_t>());

          break;
        }
        case ValueType::Int:
        {
          sm_oOpenGL.setUniformValue(sm_oOpenGL.getUniformLocation(oProgram, pAttribute->getName().c_str()),
            eType, &pAttribute->getData<int32_t>());

          break;
        }
        case ValueType::Mat4:
        {
          Mat4 temp = pAttribute->getData<Mat4>();
          float* temp2 = (float*)malloc(sizeof(float) * 16);
          
          //memcpy(temp2, temp.matrix, sizeof(float) * 16);
          for (uint32_t i = 0; i < 16; ++i)
          {
            *(temp2 + i * sizeof(float)) = temp.matrix[i];
            printf("%.10f\n", *(temp2 + i * sizeof(float)));
          }
          printf("\n");
          /*sm_oOpenGL.setUniformValue(sm_oOpenGL.getUniformLocation(oProgram, pAttribute->getName().c_str()),
            eType, pAttribute->getData<Mat4>().matrix);*/
          sm_oOpenGL.setUniformValue(sm_oOpenGL.getUniformLocation(oProgram, pAttribute->getName().c_str()),
            eType, temp2);
          free(temp2);

          break;
        }
        case ValueType::Texture:
        {
          int32_t iTextureUnit = (int32_t)pAttribute->getData<Texture>().getTextureUnit();
          sm_oOpenGL.setUniformValue(sm_oOpenGL.getUniformLocation(oProgram, pAttribute->getName().c_str()),
            eType, &iTextureUnit);

          break;
        }
      }
    }
  }
  /*
  else
  {
    // swap if else order
    Create a CommandPrepareMaterial(m_spMaterial);
  }
  */
}