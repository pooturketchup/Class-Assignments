using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using FullSailAFI.SteeringBehaviors.Core;

namespace FullSailAFI.SteeringBehaviors.StudentAI
{
    public class Flock
    {
        public float AlignmentStrength { get; set; }
        public float CohesionStrength { get; set; }
        public float SeparationStrength { get; set; }
        public List<MovingObject> Boids { get; protected set; }
        public Vector3 AveragePosition { get; set; }
        protected Vector3 AverageForward { get; set; }
        public float FlockRadius { get; set; }

        #region Constructors
        public Flock()
        {
        }
        #endregion

        #region TODO Suggested helper methods
       
        private void CalculateAverages()
        {
            Vector3 avgPos = Vector3.Empty;
             Vector3 avgForward = Vector3.Empty;

            for (int i = 0; i < Boids.Count(); i++)
            {
                avgPos += Boids[i].Position;
                avgForward += Boids[i].Velocity;
            }

            AveragePosition = avgPos / Boids.Count();
            AverageForward = avgForward / Boids.Count();

            return;
        }

        private Vector3 CalculateAlignmentAcceleration(MovingObject boid)
        {
            Vector3 pos = AverageForward / boid.MaxSpeed;
            if (pos.Length > 1)
            {
                Vector3.Normalize(pos);
            }

            return pos * AlignmentStrength;
        }

        private Vector3 CalculateCohesionAcceleration(MovingObject boid)
        {
            Vector3 pos = AveragePosition - boid.Position;
            float d = pos.Length;
            Vector3.Normalize(pos);

            if(d < FlockRadius)
            {
                pos *= d / FlockRadius;
            }
            return pos * CohesionStrength;
        }

        private Vector3 CalculateSeparationAcceleration(MovingObject boid)
        {
            Vector3 sum = Vector3.Empty;

            foreach(MovingObject otherBoid in Boids)
            {
                Vector3 pos = boid.Position - otherBoid.Position;
                float d = pos.Length;
                float safeDistance = boid.SafeRadius + otherBoid.SafeRadius;

                if(d < safeDistance)
                {
                    Vector3.Normalize(pos);
                    pos *= (safeDistance - d) / safeDistance;
                    sum += pos;
                }
            }
         
            if(sum.Length > 1.0f)
            {
                Vector3.Normalize(sum);
            }

            return sum * SeparationStrength;
        }

        #endregion

        #region TODO

        public virtual void Update(float deltaTime)
        {
            Vector3 accel = Vector3.Empty;
            float accelMultiplier = 0;

            CalculateAverages();

            foreach(MovingObject boid in Boids)
            {
                accel = CalculateAlignmentAcceleration(boid);
                accel += CalculateCohesionAcceleration(boid);
                accel += CalculateSeparationAcceleration(boid);
                accelMultiplier = boid.MaxSpeed;
                accel *= accelMultiplier * deltaTime;

                boid.Velocity += accel;

                if(boid.Velocity.Length > boid.MaxSpeed)
                {
                    Vector3.Normalize(boid.Velocity);
                    boid.Velocity *= boid.MaxSpeed;
                }

                boid.Update(deltaTime);
            }


            return;
        }
        #endregion
    }
}
