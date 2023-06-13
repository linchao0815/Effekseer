using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Effekseer.Utils;

namespace Effekseer.Binary
{
	class GpuParticlesValues
	{
		public static byte[] GetBytes(Data.GpuParticlesValues value, 
			SortedDictionary<string, int> colorTexAndIndex, 
			SortedDictionary<string, int> normalTexAndIndex,
			SortedDictionary<string, int> modelAndIndex)
		{
			List<byte[]> data = new List<byte[]>();

			data.Add(value.Enabled.Value.GetBytes());
			if (!value.Enabled.Value)
			{
				return value.Enabled.Value.GetBytes();
			}

			data.Add(value.Basic.EmitCount.GetBytes());

			data.Add(value.Basic.LifeTime.GetBytes());
			data.Add(value.Basic.EmitOffset.GetBytes());
			data.Add(value.Basic.EmitInterval.GetBytes());

			data.Add(value.Position.Direction.GetBytes());
			data.Add(value.Position.Spread.GetBytes());
			data.Add(value.Position.InitialSpeed.GetBytes());
			data.Add(value.Position.Damping.GetBytes());

			data.Add(value.Rotation.InitialAngle.GetBytes());
			data.Add(value.Rotation.AngularVelocity.GetBytes());

			data.Add(value.Scale.InitialScale.GetBytes());
			data.Add(value.Scale.TerminalScale.GetBytes());

			data.Add(value.Force.Gravity.GetBytes(1.0f / 60.0f));
			data.Add(value.Force.Vortex.Rotation.GetBytes(1.0f / 60.0f));
			data.Add(value.Force.Vortex.Attraction.GetBytes(1.0f / 60.0f));
			data.Add(value.Force.Vortex.Center.GetBytes());
			data.Add(value.Force.Vortex.Axis.GetBytes());
			data.Add(value.Force.Turbulence.Power.GetBytes(1.0f / 60.0f));
			data.Add(value.Force.Turbulence.Seed.GetBytes());
			data.Add(value.Force.Turbulence.Scale.GetBytes());
			data.Add(value.Force.Turbulence.Octave.GetBytes());

			data.Add(((byte)value.RenderBasic.BlendType.Value).GetBytes());
			data.Add(((byte)(value.RenderBasic.ZWrite.Value ? 1 : 0)).GetBytes());
			data.Add(((byte)(value.RenderBasic.ZTest.Value ? 1 : 0)).GetBytes());
			data.Add(((byte)0).GetBytes());

			// RenderShapeParams
			data.Add(value.RenderShape.Shape.GetBytes());
			switch (value.RenderShape.Shape.Value)
			{
				case Data.GpuParticlesValues.RenderShapeParams.ShapeType.Sprite:
					data.Add(value.RenderShape.SpriteBillboard.GetBytes());
					break;
				case Data.GpuParticlesValues.RenderShapeParams.ShapeType.Model:
					AddResource(data, modelAndIndex, value.RenderShape.ModelPath);
					break;
				case Data.GpuParticlesValues.RenderShapeParams.ShapeType.Trail:
					data.Add(value.RenderShape.TrailLength.GetBytes());
					break;
			}
			data.Add(value.RenderShape.ShapeSize.GetBytes());

			// RenderColorParams
			data.Add(value.RenderColor.ColorInheritType.GetBytes());
			data.Add(value.RenderColor.ColorAll.Type.GetBytes());
			switch (value.RenderColor.ColorAll.Type.Value)
			{
				case Data.StandardColorType.Fixed:
					data.Add(value.RenderColor.ColorAll.Fixed.GetBytes());
					break;
				case Data.StandardColorType.Random:
					data.Add(value.RenderColor.ColorAll.Random.GetBytes());
					break;
				case Data.StandardColorType.Easing:
					data.Add(value.RenderColor.ColorAll.Easing.Start.GetBytes());
					data.Add(value.RenderColor.ColorAll.Easing.End.GetBytes());
					break;
			}
			data.Add(value.RenderColor.Emissive.GetBytes());
			data.Add(value.RenderColor.FadeIn.GetBytes());
			data.Add(value.RenderColor.FadeOut.GetBytes());

			// RenderMaterialParams
			AddResource(data, colorTexAndIndex, value.RenderMaterial.ColorTexture.Path);
			AddResource(data, normalTexAndIndex, value.RenderMaterial.NormalTexture.Path);
			data.Add(((byte)value.RenderMaterial.ColorTexture.Filter.Value).GetBytes());
			data.Add(((byte)value.RenderMaterial.NormalTexture.Filter.Value).GetBytes());
			data.Add(((byte)value.RenderMaterial.ColorTexture.Wrap.Value).GetBytes());
			data.Add(((byte)value.RenderMaterial.NormalTexture.Wrap.Value).GetBytes());

			return data.ToArray().ToArray();
		}

		private static void AddResource(List<byte[]> data, SortedDictionary<string, int> pathToIdx, Data.Value.Path path)
		{
			if (pathToIdx.ContainsKey(path.RelativePath))
			{
				data.Add(pathToIdx[path.RelativePath].GetBytes());
			}
			else
			{
				data.Add((-1).GetBytes());
			}
		}
	}
}