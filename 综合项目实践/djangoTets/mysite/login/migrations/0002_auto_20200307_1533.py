# Generated by Django 2.2.4 on 2020-03-07 07:33

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('login', '0001_initial'),
    ]

    operations = [
        migrations.AddField(
            model_name='draw',
            name='number',
            field=models.IntegerField(default=0),
        ),
        migrations.AlterField(
            model_name='draw',
            name='onDoing',
            field=models.CharField(choices=[('1', '是'), ('2', '否')], max_length=2),
        ),
    ]
