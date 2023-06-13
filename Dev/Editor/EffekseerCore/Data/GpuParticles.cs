using Effekseer.Data.Group;
using Effekseer.Data.Value;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using static Effekseer.Data.RendererCommonValues;

namespace Effekseer.Data
{
	public class GpuParticlesValues
	{
		public class BasicParams
		{
			[Key(key = "GpuParticles_Basic_EmitCount")]
			public Value.IntWithInifinite EmitCount { get; private set; } = new Value.IntWithInifinite(value: 20, min: 1);

			[Key(key = "GpuParticles_Basic_LifeTime")]
			public Value.IntWithRandom LifeTime { get; private set; } = new Value.IntWithRandom(value: 100, min: 1);

			[Key(key = "GpuParticles_Basic_EmitOffset")]
			public Value.FloatWithRandom EmitOffset { get; private set; } = new Value.FloatWithRandom(value: 0.0f, min: 0.0f);

			[Key(key = "GpuParticles_Basic_EmitInterval")]
			public Value.FloatWithRandom EmitInterval { get; private set; } = new Value.FloatWithRandom(value: 1.0f, min: 0.0f);
		}

		public class PositionParams
		{
			[Key(key = "GpuParticles_Position_Direction")]
			public Value.Vector3D Direction { get; private set; } = new Value.Vector3D(0.0f, 0.0f, 1.0f);

			[Key(key = "GpuParticles_Position_Spread")]
			public Value.Float Spread { get; private set; } = new Value.Float(value: 15.0f, min: 0.0f, max: 180.0f);

			[Key(key = "GpuParticles_Position_InitialSpeed")]
			public Value.FloatWithRandom InitialSpeed { get; private set; } = new Value.FloatWithRandom(value: 1.0f);

			[Key(key = "GpuParticles_Position_Damping")]
			public Value.FloatWithRandom Damping { get; private set; } = new Value.FloatWithRandom(value: 0.0f, min: 0.0f);
		}

		public class RotationParams
		{
			[Key(key = "GpuParticles_Rotation_InitialAngle")]
			public Value.Vector3DWithRandom InitialAngle { get; private set; } = new Value.Vector3DWithRandom();

			[Key(key = "GpuParticles_Rotation_AngularVelocity")]
			public Value.Vector3DWithRandom AngularVelocity { get; private set; } = new Value.Vector3DWithRandom();
		}

		public class ScaleParams
		{
			[Key(key = "GpuParticles_Scale_InitialScale")]
			public Value.FloatWithRandom InitialScale { get; private set; } = new Value.FloatWithRandom(1.0f);

			[Key(key = "GpuParticles_Scale_TerminalScale")]
			public Value.FloatWithRandom TerminalScale { get; private set; } = new Value.FloatWithRandom(1.0f);
		}

		public class ForceParams
		{
			[Key(key = "GpuParticles_Force_Gravity")]
			public Value.Vector3D Gravity { get; private set; } = new Value.Vector3D();

			public class VortexParams
			{
				[Key(key = "GpuParticles_Force_Vortex_Rotation")]
				public Value.Float Rotation { get; private set; } = new Value.Float(0.0f);

				[Key(key = "GpuParticles_Force_Vortex_Attraction")]
				public Value.Float Attraction { get; private set; } = new Value.Float(0.0f);

				[Key(key = "GpuParticles_Force_Vortex_Center")]
				public Value.Vector3D Center { get; private set; } = new Value.Vector3D(0.0f, 0.0f, 0.0f);

				[Key(key = "GpuParticles_Force_Vortex_Axis")]
				public Value.Vector3D Axis { get; private set; } = new Value.Vector3D(0.0f, 1.0f, 0.0f);
			}

			[IO(Export = true)]
			[TreeNode(id = "GpuParticles_Force_Vortex", key = "GpuParticles_Force_Vortex", type = TreeNodeType.Small)]
			public VortexParams Vortex { get; private set; } = new VortexParams();

			public class TurbulenceParams
			{
				[Key(key = "GpuParticles_Force_Turbulence_Power")]
				public Value.Float Power { get; private set; } = new Value.Float(0.0f, min: 0.0f);

				[Key(key = "GpuParticles_Force_Turbulence_Seed")]
				public Value.Int Seed { get; private set; } = new Value.Int(0, min: 0);

				[Key(key = "GpuParticles_Force_Turbulence_Scale")]
				public Value.Float Scale { get; private set; } = new Value.Float(4.0f, min: 0.0f, step: 0.1f);

				[Key(key = "GpuParticles_Force_Turbulence_Octave")]
				public Value.Int Octave { get; private set; } = new Value.Int(1, max: 10, min: 1);
			}

			[IO(Export = true)]
			[TreeNode(id = "GpuParticles_Force_Turbulence", key = "GpuParticles_Force_Turbulence", type = TreeNodeType.Small)]
			public TurbulenceParams Turbulence { get; private set; } = new TurbulenceParams();
		}

		public class RenderBasicParams
		{
			[Key(key = "GpuParticles_RenderBasic_BlendType")]
			public Value.Enum<AlphaBlendType> BlendType { get; private set; } = new Value.Enum<AlphaBlendType>(AlphaBlendType.Blend);

			[Key(key = "GpuParticles_RenderBasic_ZWrite")]
			public Value.Boolean ZWrite { get; private set; } = new Value.Boolean(false);

			[Key(key = "GpuParticles_RenderBasic_ZTest")]
			public Value.Boolean ZTest { get; private set; } = new Value.Boolean(true);
		};

		public class RenderShapeParams
		{
			public enum ShapeType : int
			{
				[Key(key = "GpuParticles_RenderShape_ShapeType_Sprite")]
				Sprite = 0,

				[Key(key = "GpuParticles_RenderShape_ShapeType_Model")]
				Model = 1,

				[Key(key = "GpuParticles_RenderShape_ShapeType_Trail")]
				Trail = 2,
			}
			public enum BillboardType : int
			{
				[Key(key = "GpuParticles_RenderShape_BillboardType_Billboard")]
				Billboard = 0,

				[Key(key = "GpuParticles_RenderShape_BillboardType_YAxisFixed")]
				YAxisFixed = 1,

				[Key(key = "GpuParticles_RenderShape_BillboardType_Fixed")]
				Fixed = 2,
			}

			[Selector(ID = 0)]
			[Key(key = "GpuParticles_RenderShape_Shape")]
			public Value.Enum<ShapeType> Shape { get; private set; } = new Value.Enum<ShapeType>();

			[Selected(ID = 0, Value = 0)]
			[Key(key = "GpuParticles_RenderShape_SpriteBillboard")]
			public Value.Enum<BillboardType> SpriteBillboard { get; private set; } = new Value.Enum<BillboardType>();

			[Selected(ID = 0, Value = 1)]
			[Key(key = "GpuParticles_RenderShape_ModelPath")]
			public Value.PathForModel ModelPath { get; private set; } = null;

			[Selected(ID = 0, Value = 2)]
			[Key(key = "GpuParticles_RenderShape_TrailLength")]
			public Value.Int TrailLength { get; private set; } = new Value.Int(value: 16, min: 0);

			[Key(key = "GpuParticles_RenderShape_Size")]
			public Value.Float ShapeSize { get; private set; } = new Value.Float(value: 1.0f, min: 0);

			public RenderShapeParams(Value.Path basepath)
			{
				ModelPath = new Value.PathForModel(basepath, new MultiLanguageString("ModelFilter"), true, "");
			}
		}

		public class RenderColorParams
		{
			[Key(key = "GpuParticles_RenderColor_ColorInherit")]
			public Value.Enum<ParentEffectType> ColorInheritType { get; private set; } = new Value.Enum<ParentEffectType>();

			[IO(Export = true)]
			[Group]
			[Key(key = "GpuParticles_RenderColor_ColorAll")]
			public StandardColor ColorAll { get; private set; } = new StandardColor();

			[Key(key = "GpuParticles_RenderColor_Emissive")]
			public Value.Float Emissive { get; private set; } = new Value.Float(value: 1.0f, min: 0);

			[Key(key = "GpuParticles_RenderColor_FadeIn")]
			public Value.Float FadeIn { get; private set; } = new Value.Float(value: 0.0f, min: 0.0f);

			[Key(key = "GpuParticles_RenderColor_FadeOut")]
			public Value.Float FadeOut { get; private set; } = new Value.Float(value: 0.0f, min: 0.0f);
		}

		public class RenderMaterialParams
		{
			public class Texture
			{
				[Key(key = "GpuParticles_RenderMaterial_TexturePath")]
				public Value.PathForImage Path { get; private set; } = null;

				[Key(key = "GpuParticles_RenderMaterial_TextureFilter")]
				public Value.Enum<FilterType> Filter { get; private set; } = new Value.Enum<FilterType>(FilterType.Linear);

				[Key(key = "GpuParticles_RenderMaterial_TextureWrap")]
				public Value.Enum<WrapType> Wrap { get; private set; } = new Value.Enum<WrapType>(WrapType.Repeat);

				public Texture(Value.Path basepath)
				{
					Path = new Value.PathForImage(basepath, new MultiLanguageString("ModelFilter"), true, "");
				}
			}

			[IO(Export = true)]
			[Group]
			[Key(key = "GpuParticles_RenderMaterial_ColorTexture")]
			public Texture ColorTexture { get; private set; } = null;

			[IO(Export = true)]
			[Group]
			[Key(key = "GpuParticles_RenderMaterial_NormalTexture")]
			public Texture NormalTexture { get; private set; } = null;

			public RenderMaterialParams(Value.Path basepath)
			{
				ColorTexture = new Texture(basepath);
				NormalTexture = new Texture(basepath);
			}
		}

		[IO(Export = true)]
		[Selector(ID = 0)]
		[Key(key = "GpuParticles_Enabled")]
		public Value.Boolean Enabled { get; private set; } = new Value.Boolean();

		[IO(Export = true)]
		[Selected(ID = 0, Value = 1)]
		[TreeNode(id = "GpuParticles_Basic", key = "GpuParticles_Basic")]
		public BasicParams Basic { get; private set; } = new BasicParams();

		[IO(Export = true)]
		[Selected(ID = 0, Value = 1)]
		[TreeNode(id = "GpuParticles_Position", key = "GpuParticles_Position")]
		public PositionParams Position { get; private set; } = new PositionParams();

		[IO(Export = true)]
		[Selected(ID = 0, Value = 1)]
		[TreeNode(id = "GpuParticles_Rotation", key = "GpuParticles_Rotation")]
		public RotationParams Rotation { get; private set; } = new RotationParams();

		[IO(Export = true)]
		[Selected(ID = 0, Value = 1)]
		[TreeNode(id = "GpuParticles_Scale", key = "GpuParticles_Scale")]
		public ScaleParams Scale { get; private set; } = new ScaleParams();

		[IO(Export = true)]
		[Selected(ID = 0, Value = 1)]
		[TreeNode(id = "GpuParticles_Force", key = "GpuParticles_Force")]
		public ForceParams Force { get; private set; } = new ForceParams();

		[IO(Export = true)]
		[Selected(ID = 0, Value = 1)]
		[TreeNode(id = "GpuParticles_RenderBasic", key = "GpuParticles_RenderBasic")]
		public RenderBasicParams RenderBasic { get; private set; } = new RenderBasicParams();
		
		[IO(Export = true)]
		[Selected(ID = 0, Value = 1)]
		[TreeNode(id = "GpuParticles_RenderShape", key = "GpuParticles_RenderShape")]
		public RenderShapeParams RenderShape { get; private set; } = null;

		[IO(Export = true)]
		[Selected(ID = 0, Value = 1)]
		[TreeNode(id = "GpuParticles_RenderColor", key = "GpuParticles_RenderColor")]
		public RenderColorParams RenderColor { get; private set; } = new RenderColorParams();

		[IO(Export = true)]
		[Selected(ID = 0, Value = 1)]
		[TreeNode(id = "GpuParticles_RenderMaterial", key = "GpuParticles_RenderMaterial")]
		public RenderMaterialParams RenderMaterial { get; private set; } = null;

		public GpuParticlesValues(Value.Path basepath)
		{
			RenderShape = new RenderShapeParams(basepath);
			RenderMaterial = new RenderMaterialParams(basepath);
		}
	}
}
