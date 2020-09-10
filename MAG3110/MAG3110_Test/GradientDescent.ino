void Gradient(vector* _mag,vector* _earth,quarternion* Qt)
{
  boolean OnceFlag = true;
  boolean ObjectiveMet = false;
  int LoopCounter = -1;

  float StepSize = 0.25f;
  float norm;

  float R[3][3];
  float F[3];
  float JF[3][4];

  quarternion Qp;

  Qp.w = Qt->w;
  Qp.x = Qt->x;
  Qp.y = Qt->y;
  Qp.z = Qt->z;
  
  while (LoopCounter < 100 && !ObjectiveMet)
  {
    LoopCounter++;
   
    R[0][0] = 2*(0.5f - Qp.y*Qp.y - Qp.z*Qp.z);
    R[0][1] = 2*(Qp.x*Qp.y + Qp.w*Qp.z);
    R[0][2] = 2*(Qp.x*Qp.z - Qp.w*Qp.y);
  
    R[1][0] = 2*(Qp.x*Qp.y - Qp.w*Qp.z);
    R[1][1] = 2*(0.5f - Qp.x*Qp.x - Qp.z*Qp.z);
    R[1][2] = 2*(Qp.y*Qp.z + Qp.w*Qp.x);
  
    R[2][0] = 2*(Qp.x*Qp.z + Qp.w*Qp.y);
    R[2][1] = 2*(Qp.y*Qp.z - Qp.w*Qp.x) ;
    R[2][2] = 2*(0.5f - Qp.x*Qp.x - Qp.y*Qp.y);
       
    F[0] = (R[0][0]*_earth->x + R[0][2]*_earth->z) - _mag->x;
    F[1] = (R[1][0]*_earth->x + R[1][2]*_earth->z) - _mag->y;
    F[2] = (R[2][0]*_earth->x + R[2][2]*_earth->z) - _mag->z;

    if(0.5f * (F[0]*F[0] + F[1]*F[1] + F[2]*F[2]) > 0.0005f)
    {
      JF[0][0] = -2.0f * _earth->z * Qp.y;
      JF[0][1] =  2.0f * _earth->z * Qp.z;
      JF[0][2] = -4.0f * _earth->x * Qp.y - 2.0f * _earth->z * Qp.w;
      JF[0][3] = -4.0f * _earth->x * Qp.z + 2.0f * _earth->z * Qp.x;

      JF[1][0] = -2.0f * _earth->x * Qp.z + 2.0f * _earth->z * Qp.x;
      JF[1][1] =  2.0f * _earth->x * Qp.y + 2.0f * _earth->z * Qp.w;
      JF[1][2] =  2.0f * _earth->x * Qp.x + 2.0f * _earth->z * Qp.z;
      JF[1][3] = -2.0f * _earth->x * Qp.w + 2.0f * _earth->z * Qp.y;
        
      JF[2][0] =  2.0f * _earth->x * Qp.y;
      JF[2][1] =  2.0f * _earth->x * Qp.z - 4.0f * _earth->z * Qp.x;
      JF[2][2] =  2.0f * _earth->x * Qp.w - 4.0f * _earth->z * Qp.y;
      JF[2][3] =  2.0f * _earth->x * Qp.x;

      Qp.w -= StepSize*(F[0]*JF[0][0] + F[1]*JF[1][0] + F[2]*JF[2][0] + F[3]*JF[3][0]);
      Qp.x -= StepSize*(F[0]*JF[0][1] + F[1]*JF[1][1] + F[2]*JF[2][1] + F[3]*JF[3][1]);
      Qp.y -= StepSize*(F[0]*JF[0][2] + F[1]*JF[1][2] + F[2]*JF[2][2] + F[3]*JF[3][2]);
      Qp.z -= StepSize*(F[0]*JF[0][3] + F[1]*JF[1][3] + F[2]*JF[2][3] + F[3]*JF[3][3]);

      norm = 1.0f / sqrt(Qp.w*Qp.w + Qp.x*Qp.x + Qp.y*Qp.y + Qp.z*Qp.z);
      Qp.w *= norm;
      Qp.x *= norm;
      Qp.y *= norm;
      Qp.z *= norm;
    } else 
      {
        //ObjectiveMet = true;
      }
  }
  Serial.print(LoopCounter);
  Serial.print('\t');
  Qt->w = Qp.w;
  Qt->x = Qp.x;
  Qt->y = Qp.y;
  Qt->z = Qp.z;
}


    
    
