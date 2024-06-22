find ./ -name "*.png" -exec ffmpeg -i "{}" "{}".webp \; -exec rename 's/\.webp//' {} \;

