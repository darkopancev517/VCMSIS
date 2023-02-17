<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>Zertifikate | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="vpn-android-galaxys4.php" title="46. Kapitel - VPN mit Android"><link rel="prev" href="vpn-android-galaxys4.php" title="46. Kapitel - VPN mit Android"><link rel="next" href="vpn-android-galaxys4-connection-intranator.php" title="46.3. Verbindung auf dem Intranator">
    <meta http-equiv="content-language" content="de">
  </head><body>
          
    <!-- header start -->

<div id="header">

<div id="logo">
	<a href="../../../index.html">
		<div id="logo_screen"><img src="../../../pictures/intra2net.gif" alt="Intra2net AG"></div>
		<div id="logo_print"><img src="../../../pictures/intra2net_print.gif" alt="Intra2net AG"></div>
	</a>
</div>

<div id="search">
	<form name="formsearch" method="get" action="http://www.intra2net.com/search/search.cgi">
		<input type="text" name="q" maxlength="64" id="searchinput" value="">
		<input type="image" name="submit" src="../../../pictures/search.gif" alt="Suche">
	</form>
</div>


<nav id="navigation">

<a href="vpn-android-certificates.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="vpn-android-certificates.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

<ul class="navbar">

<li id="Produkte"><a href="../../../../en/products/index.html">Produkte</a>
	<div class="dropdown">
		<div class="navgrid">
			<div class="navgrid-unit navcol1_of_3">
				<h4>SOFTWARE</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/index.php">&Uuml;bersicht</a></li>
						<li><a href="../../../produkte/intranator.php">Business Server</a></li>
						<li><a href="../../../produkte/security_gateway.php">Security Gateway</a></li>
						<li><a href="../../../produkte/network_security.php">Network Security</a></li>
						<li><a href="../../../produkte/lizenzen/index.php">Lizenzbestimmungen</a></li>
					</ul>
			</div>
			<div class="navgrid-unit navcol1_of_3">
				<h4>HARDWARE</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/hardware.php">&Uuml;bersicht</a></li>
						<li><a href="../../../produkte/appliance_eco.php">Appliance Eco</a></li>
						<li><a href="../../../produkte/appliance_pro.php">Appliance Pro</a></li>
						<li><a href="../../../produkte/appliance_ultimate.php">Appliance Ultimate</a></li>
					</ul>
			</div>
			<div class="navgrid-unit navcol1_of_3">
				<h4>REFERENZEN</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/anwenderberichte.php">Anwenderberichte</a></li>
						<li><a href="../../../produkte/kundenstimmen.php">Kundenstimmen</a></li>
						<li><a href="../../../produkte/pressestimmen.php">Pressestimmen</a></li>
					</ul>
			</div>
		</div> <!-- close .grid div -->
	</div> <!-- close .dropdown div -->
</li>

<li id="Download"><a href="../../../download.1">Download</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../download/index.php">Software</a></li>
			<li><a href="../../../download/datenblaetter.php">Datenbl&auml;tter</a></li>
			<li><a href="../../../download/handbuecher.php">Handb&uuml;cher</a></li>
		</ul>
	</div>
</li>

<li id="Support" class="selected"><a href="../../../../en/support/index.html">Support</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../anfrage.php">Support-Anfrage</a></li>
			<li><a href="../../handbuecher.php">Handb&uuml;cher</a></li>
			<li><a href="http://forum.intra2net.com/">Forum</a></li>
			<li><a href="../../unterstuetzte_hardware.php">Unterst&uuml;tzte Hardware</a></li>
			<li><a href="../../antispam/index.html">Blacklist Performance</a></li>
			<li><a href="../../schulung.php">Schulung</a></li>
			<li><a href="../../fernwartung.php">Fernwartung</a></li>
		</ul>
	</div>
</li>

<li id="Kaufen"><a href="../../../kaufen/index.html">Kaufen</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../kaufen/index.php">Partner finden</a></li>
			<li><a href="../../../partner-werden">Partner werden</a></li>
			<li><a href="http://partner.intra2net.com/">Partnerweb</a></li>
		</ul>
	</div>
</li>

<li id="Unternehmen"><a href="../../../unternehmen/index.html">Unternehmen</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../unternehmen/index.php">&Uuml;ber Intra2net</a></li>
			<li><a href="../../../unternehmen/presse/index.php">Presse</a></li>
			<li><a href="../../../unternehmen/karriere.php">Karriere</a></li>
			<li><a href="../../../unternehmen/kontakt.php">Kontakt</a></li>
		</ul>
	</div>
</li>

</ul> <!-- close #navbar ul -->

</nav>

</div> <!-- close #header div -->


<div id="page">


<div id="content">

<!-- header end -->

    <div id="manual">
    <!-- content start -->

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">46.2. Zertifikate</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="vpn-android-galaxys4.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">46. Kapitel - VPN mit Android</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="vpn-android-galaxys4-connection-intranator.php">Weiter</a></td></tr></table><hr></div><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="vpn-android-certificates"></a>46.2. Zertifikate</h2></div></div></div><div class="procedure"><ol type="1"><li><p>Android kann selbst keine eigenen Zertifikate erstellen. Dies &uuml;bernimmt daher das
          Programm <code class="computeroutput">makecert</code> auf einem PC.</p><p>Laden Sie vom Intranator unter
            <span class="guimenu">Information&nbsp;&gt;&nbsp;Download</span> das
            <code class="computeroutput">Programm zum Erzeugen von Zertifikaten (makecert)</code>
          herunter und entpacken Sie es in ein Verzeichnis auf Ihrem Rechner.</p></li><li><p>Starten Sie die <span class="command"><strong>makecert</strong></span>-Batchdatei.</p><pre class="programlisting">C:\makecert&gt;makecert
Gueltigkeit des neuen Zertifikats:
1. Ein Jahr
2. Zwei Jahre
3. Drei Jahre
4. Vier Jahre
5. Fuenf Jahre
Ihre Wahl: 5
            
C:\makecert&gt;openssl req -x509 -newkey rsa:2048 -days 1825 -new -nodes -config 
openssl.cnf -outform PEM -keyform PEM -keyout privatekey.pem -out newcert.cer
Using configuration from openssl.cnf
Loading 'screen' into random state - done
Generating a 2048 bit RSA private key
........................+++
...............................................................+++
writing new private key to 'privatekey.pem'
-----
You are about to be asked to enter information that will be incorporated
into your certificate request.
What you are about to enter is what is called a Distinguished Name or a DN.
There are quite a few fields but you can leave some blank
For some fields there will be a default value,
If you enter '.', the field will be left blank.</pre></li><li><p>Geben Sie jetzt die Daten des Rechners ein. F&uuml;r einige Felder gibt es einen
          Standardwert der in eckigen Klammern angegeben ist. Wollen Sie diesen verwenden, so
          dr&uuml;cken Sie einfach nur Return. Verwenden Sie keine Umlaute und andere Sonderzeichen, da
          es sonst zu Problemen kommen kann. Der &#8220;Common Name&#8221; (oder &#8220;Rechnername&#8221; auf dem
          Intranator) muss eindeutig sein und darf nicht auf anderen Rechnern oder f&uuml;r eine CA
          wiederverwendet werden.</p><pre class="programlisting">Country Name (2 letter code) []:
State or Province Name (full name) []:
Locality Name (eg, city) []:
Organization Name (eg, company) []:Firma GmbH
Organizational Unit Name (eg, section) []:
Common Name (eg, your name or your server's hostname) []:Android Mueller
Email Address []:

C:\makecert&gt;openssl pkcs12 -export -in newcert.cer -inkey privatekey.pem 
-out newcert.p12
Loading 'screen' into random state - done</pre></li><li><p>W&auml;hlen Sie ein Transportpasswort, mit dem die Schl&uuml;sseldatei auf dem Weg zum
          VPN-Client im Ger&auml;t gesch&uuml;tzt wird. Das Passwort muss mindestens 4 Zeichen lang
          sein.</p><pre class="programlisting">Enter Export Password:
Verifying password - Enter Export Password:

C:\makecert&gt;del privatekey.pem</pre></li><li><p>Das Schl&uuml;sselpaket f&uuml;r den Client liegt nun im PKCS#12-Format in der Datei
            <code class="computeroutput">newkey.p12</code>, das Zertifikat f&uuml;r den Intranator
          (PEM-Format) in der Datei <code class="computeroutput">newkey_cert.cer</code>.</p></li><li><p>Das Zertifikat des Clients wird nun dem Intranator bekannt gemacht. &Ouml;ffnen Sie dazu
          die Zertifikatsdatei (<code class="computeroutput">newkey_cert.cer</code>) mit einem
          Texteditor (z.B. Wordpad) und &uuml;bernehmen den gesamten Inhalt der Datei in die
          Zwischenablage.</p></li><li><p>&Ouml;ffnen Sie im Intranator das Men&uuml; System&nbsp;&gt; Schl&uuml;ssel&nbsp;&gt;
          Fremde Schl&uuml;ssel und legen einen neuen an. Vergeben Sie einen Namen f&uuml;r den Schl&uuml;ssel
          (z.B. den Namen des Mitarbeiters) und f&uuml;gen dann die Zertifikatsdaten aus der
          Zwischenablage in das Feld "Copy &amp; Paste Schl&uuml;ssel" ein.</p></li><li><p>Als n&auml;chstes bereiten wir das Zertifikat des Intranators f&uuml;r den Import in Android
          vor. &Ouml;ffnen Sie dazu das Men&uuml; System&nbsp;&gt; Schl&uuml;ssel&nbsp;&gt; Eigene
          Schl&uuml;ssel und w&auml;hlen das Zertifikat aus, das Sie f&uuml;r die Verbindung verwenden wollen. Es
          bietet sich an, f&uuml;r alle VPNs auf Seite des Intranators nur ein Zertifikat zu verwenden.
          Exportieren Sie nun das Zertifikat als .cer-Datei auf Ihren lokalen Rechner.</p></li><li><p>Verbinden Sie nun das Android-Ger&auml;t per USB mit Ihrem Rechner. Bei vielen Ger&auml;ten
          haben Sie verschiedene Verbindungsmodi zur Auswahl. W&auml;hlen Sie einen Modus, in dem Sie
          Dateien zwischen PC und Android-Ger&auml;t austauschen k&ouml;nnen, z.B. Medienger&auml;t (MTP) oder
          Laufwerk. Konsultieren Sie bei Unklarheiten das Handbuch Ihres Android-Ger&auml;ts zum Thema
          Datenaustausch zwischen PC und Ger&auml;t.</p></li><li><p>Kopieren Sie nun (z.B. mit dem Windows Explorer) das vorher erstellte Schl&uuml;sselpaket
          (Dateiname <code class="filename">newcert.p12</code>) in das Wurzelverzeichnis des
          Android-Laufwerks.</p></li><li><p>Kopieren Sie auch die eben mit dem Browser heruntergeladene Zertifikatsdatei des
          Intranators in das Wurzelverzeichnis des Android-Laufwerks. Der Dateiname ist der im
          Intranator vergebene Name mit der Endung <code class="filename">.cer</code>.</p></li><li><p>Trennen Sie die Verbindung zwischen PC und Android-Ger&auml;t ordnungsgem&auml;&szlig; &uuml;ber die
          Trennen-Funktion in der Taskleiste von Windows.</p></li><li><p>&Ouml;ffnen Sie auf dem Android-Ger&auml;t die <span class="guimenu">Einstellungen</span>, Reiter
            <span class="guisubmenu">Optionen</span>, <span class="guimenuitem">Sicherheit</span>.</p><div class="mediaobject"><img src="../images/vpn/android-galaxys4/cert-install01.png"></div></li><li><p>&Ouml;ffnen Sie in der Kategorie <span class="guisubmenu">Berechtigungsspeicher</span> den
          Men&uuml;punkt <span class="guimenuitem">Von USB-Speicher installieren</span>. </p><div class="informaltable"><table border="0"><colgroup><col><col></colgroup><tbody><tr><td align="left">
                  <div class="mediaobject"><img src="../images/vpn/android-galaxys4/cert-install02.png"></div>
                </td><td align="left">
                  <div class="mediaobject"><img src="../images/vpn/android-galaxys4/cert-install03.png"></div>
                </td></tr></tbody></table></div></li><li><p>Klicken Sie den privaten Schl&uuml;ssel (Dateiname <code class="filename">newcert.p12</code>) an um
          diesen zu importieren. Sie werden nach dem vorhin vergebenen Transportpasswort gefragt und
          bekommen dann die M&ouml;glichkeit, einen passenden Namen f&uuml;r das Zertifikat zu vergeben.</p><div class="informaltable"><table border="0"><colgroup><col><col></colgroup><tbody><tr><td align="left">
                  <div class="mediaobject"><img src="../images/vpn/android-galaxys4/cert-install04.png"></div>
                </td><td align="left">
                  <div class="mediaobject"><img src="../images/vpn/android-galaxys4/cert-install05.png"></div>
                </td></tr></tbody></table></div></li><li><p>Klicken Sie das Zertifikat des Intranators an und vergeben einen passenden
          Namen.</p><div class="mediaobject"><img src="../images/vpn/android-galaxys4/cert-install06.png"></div></li><li><p>Die Zertifikate sind nun zwischen den Ger&auml;ten ausgetauscht und installiert.</p></li></ol></div></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="vpn-android-galaxys4.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="vpn-android-galaxys4.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="vpn-android-galaxys4-connection-intranator.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">46. Kapitel - VPN mit Android&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;46.3. Verbindung auf dem Intranator</td></tr></table></div>
      
    <!-- content end -->
    </div>

  <!-- footer start -->

</div> <!-- close content <div> -->
</div> <!-- close page <div> -->

<div id="sitemap">

<div id="sitemapcol1">
	<a href="../../../produkte/index.php" class="sitemapheader">Produkte</a>
	<ul class="sitemap">
	<li><a href="../../../produkte/intranator.php">Intra2net Business Server</a></li>
	<li><a href="../../../produkte/security_gateway.php">Intra2net Security Gateway</a></li>
	<li><a href="../../../produkte/network_security.php">Intra2net Network Security</a></li>
	<li><a href="../../../produkte/appliance_eco.php">Intra2net Appliance Eco</a></li>
	<li><a href="../../../produkte/appliance_pro.php">Intra2net Appliance Pro</a></li>
	<li><a href="../../../produkte/appliance_ultimate.php">Intra2net Appliance Ultimate</a></li>
	</ul>
</div>

<div id="sitemapcol2">
	<a href="../../../download/index.php" class="sitemapheader">Download</a>
	<ul class="sitemap">
	<li><a href="../../../download/index.php">Software</a></li>
	<li><a href="../../../download/datenblaetter.php">Datenbl&auml;tter</a></li>
	<li><a href="../../../download/handbuecher.php">Handb&uuml;cher</a></li>
	</ul>
</div>

<div id="sitemapcol3">
	<a href="../../index.php" class="sitemapheader">Support</a>
	<ul class="sitemap">
	<li><a href="../../anfrage.php">Support-Anfrage</a></li>
	<li><a href="../../handbuecher.php">Handb&uuml;cher</a></li>
	<li><a href="http://forum.intra2net.com/">Forum</a></li>
	<li><a href="../../unterstuetzte_hardware.php">Unterst&uuml;tzte Hardware</a></li>
	<li><a href="../../antispam/index.html">Blacklist Performance</a></li>
	<li><a href="../../schulung.php">Schulung</a></li>
	<li><a href="../../fernwartung.php">Fernwartung</a></li>
	</ul>
</div>

<div id="sitemapcol4">
	<a href="../../../kaufen/index.php" class="sitemapheader">Kaufen</a>
	<ul class="sitemap">
	<li><a href="../../../kaufen/index.php">Partner finden</a></li>
	<li><a href="../../../partner-werden">Partner werden</a></li>
	<li><a href="https://partner.intra2net.com/">Partnerweb</a></li>
	</ul>
</div>

<div id="sitemapcol5">
	<a href="../../../unternehmen/index.php" class="sitemapheader">Unternehmen</a>
	<ul class="sitemap">
	<li><a href="../../../unternehmen/index.php">&Uuml;ber Intra2net</a></li>
	<li><a href="../../../unternehmen/presse/index.php">Presse</a></li>
	<li><a href="../../../unternehmen/karriere.php">Karriere</a></li>
	<li><a href="../../../unternehmen/kontakt.php">Kontakt</a></li>
	</ul>
</div>

</div> <!-- close sitemap <div> -->


<div id="footnote">
	<div id="footnotecompany">

		&copy; Intra2net AG 2015
	</div>

	<div id="footnotelinks">
		<a href="../../../impressum.php">Impressum</a>
		<a href="../../../../en/developer/index.html">Entwickler</a>
		<a href="../../../datenschutz.php">Datenschutz</a>
		<a href="../../../unternehmen/kontakt.php">Kontakt</a>
	</div>
</div>

<script type="text/javascript">

  var _gaq = _gaq || [];
  _gaq.push(['_setAccount', 'UA-151599-1']);
  _gaq.push(['_gat._anonymizeIp'])
  _gaq.push(['_trackPageview']);

  (function() {
    var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
    ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
  })();

</script>

<!-- PHP error counter: 0 -->

<!-- footer end -->

    </body></html>